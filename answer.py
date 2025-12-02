import importlib
import configparser
import load
from colorama import Fore
import base64
import os
from typing import List, Optional
import time
from openai import OpenAI
import httpx
from conversationStyleExtract import ChatContent
config = configparser.ConfigParser()
config.read('config.ini', encoding='utf-8')
modelName: str = config['general']['modelName']
server_url: str=config['general']['server_url']
isVisionModel: bool=config.getboolean('general', 'isVisionModel')
maxImageCount=config.getint('general', 'maxImageCount')


API_KEY=config['general']['API_KEY']


if API_KEY=='None':
    API_KEY=None
useOllama=False
builtInLanguageModel=False
ollama=None

MAX_LENGTH=5000

if server_url=='Ollama':
    ollama=importlib.import_module('ollama')
    useOllama=True
if server_url=='builtin':
    builtInLanguageModel=True
    tinylm=importlib.import_module('TinyLangJaccard')

# check the model is exist or not
print('Model:',modelName)
if useOllama:
    try:
        ollama.chat(modelName) # type: ignore
    except ollama.ResponseError as e:  # type: ignore
        print('错误：', e.error)
        if e.status_code == 404:
            print('模型未找到，正在下载...')
            load.startLoading(Fore.YELLOW,'正在下载模型...')
            ollama.pull(modelName)  # type: ignore
            load.stopLoading()

import base64
import os

def _imageToBase64(path: str) -> str:
    with open(path, "rb") as f:
        return base64.b64encode(f.read()).decode("utf-8")

import re
from pathlib import Path

def isTime(text):
    # 正则表达式匹配 HH:MM 格式，括号可选
    pattern = r'\(?([0-2]?[0-9]):([0-5][0-9])\)?'
    pattern2 = r'\(?([0-2]?[0-9]).([0-5][0-9])\)?'
    
    matches = re.findall(pattern, text)
    matches.extend(re.findall(pattern2, text))
    valid_times = []
    for hour_str, minute_str in matches:
        # 补全为两位数并转换为整数
        hour = int(hour_str)
        minute = int(minute_str)
        
        # 验证时间有效性：小时 0-23，分钟 0-59（minute 已由正则保证）
        if 0 <= hour <= 23:
            valid_times.append(f"{hour:02d}:{minute:02d}")
    
    return len(valid_times) > 0, valid_times


def concatenateText(text:list[ChatContent],images):
    message=[]
    textList=text
    for t in textList[:-1]:
        if str(t)=='':
            continue
        if not t.ownByMyself:
            message.append({"role": "user", "content": str(t)})
        else:
            message.append({"role": "assistant", "content": str(t)})
    if len(textList)<1:
        textList=['']
    if isVisionModel and images:
        message.append({"role": "user", "content":str(textList[-1]), "images": [p for p in images if os.path.exists(p)]})
    else:
        message.append({"role": "user", "content":str(textList[-1])})
    if len(message)<1:
        message.append({"role": "user", "content":"_"})
    return message
def getAnswer(text:list[ChatContent]) -> Optional[str]:
    """
    调用 AI 模型获取回答（支持纯文本或图文输入）。
    
    Args:
        text: 用户问题文本
        imageList: 本地图像路径列表（仅 vision 模型有效）
    
    Returns:
        模型返回的文本，或 None（出错时）
    """

    
    if builtInLanguageModel:
        for t in text[::-1]:
            if t.text == '':
                continue
            if t.ownByMyself:
                continue
            return tinylm.answer(t.text)
        return ''
    


    # 获取系统提示
    system_prompt = config.get('general', 'system')
    if system_prompt == 'None':
        system_prompt = ''
    imageList=[]
    imageCount=0
    for t in text:
        if not t.ownByMyself:
            for i in t.imagePaths:
                if os.path.exists(i):
                   imageList.append(i)
                   imageCount+=1
                   if imageCount>=maxImageCount:
                       break
                else:
                   print(f"× 没有找到图片 {i}")
            if imageCount>=maxImageCount:
                break
        if imageCount>=maxImageCount:
            break
    # 构建消息

    
    if useOllama:
        messages = []
        if system_prompt:
            messages.append({"role": "system", "content": system_prompt})
        messages+=concatenateText(text,imageList)
        print(f"Ollama request: {messages}")
        try:
            response = ollama.chat( # type: ignore
                    model=modelName,
                    messages=messages,
                    
                    
                    stream=True
                )

            result = ''
            length = 0
            for chunk in response:
                token = chunk['message']['content']
                result += token
                length += len(token)
                if length >= MAX_LENGTH:
                    break
                print(token, end='', flush=True)
            print()  # 换行
            return result
        except Exception as e:
            print(f"Ollama request failed: {e}")
            return None
            
    else:
        try:
                client = OpenAI(
                    api_key=API_KEY,
                    base_url=server_url,
                    timeout=httpx.Timeout(30.0),
                    max_retries=2
                )

                messages = []
                if system_prompt:
                    messages.append({"role": "system", "content": system_prompt})
                text2=''
                for t in text:
                    if t.ownByMyself:

                        text2+='[你]'+str(t)
                    else:
                        text2+=str(t)
                user_content: List[dict] = [{"type": "text", "text":text2 }]

                # 如果是 Vision 模型且提供了图像，则添加图像
                if isVisionModel and imageList:
                    for img_path in imageList:
                        if not os.path.isfile(img_path):
                            print(f"[ERROR] Image file not found: {img_path}")
                            continue
                        
                        # 将图像转为 data URL（base64）
                        b64_image = _imageToBase64(img_path)
                        mime_type = "image/jpeg" if img_path.lower().endswith(('.jpg', '.jpeg')) else "image/png"
                        user_content.append({
                            "type": "image_url",
                            "image_url": {
                                "url": f"data:{mime_type};base64,{b64_image}"
                            }
                        })

                messages.append({"role": "user", "content": user_content if isVisionModel and imageList else text2})

                response = client.chat.completions.create(
                    model=modelName,
                    messages=messages,
                    max_tokens=MAX_LENGTH,
                    temperature=0.7,
                )

                answer: str = response.choices[0].message.content.strip() # type: ignore
                print(answer)
                return answer

        except Exception as e:
            print(f"[ERROR] Failed to get answer: {e}")
            # raise e
            return None
                

if __name__ == '__main__':
    ollama=importlib.import_module('ollama')
    tinylm=importlib.import_module('TinyLangJaccard')
    c=ChatContent(
        username='',
        imagePaths=[],
        text='解释图片\n2\n3\n4\n5',
        time=f'{time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())}',
        ownByMyself=False
    )
    c2=ChatContent(
        username='',
        imagePaths=[r"D:\Pictures\111.PNG"],
        text='12345',
       time=f'{time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())}',
        ownByMyself=True
    )
    c3=ChatContent(
        username='',
        imagePaths=[],
        text='678910',
        time=f'{time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())}',
        ownByMyself=False
    )


    useOllama=True
    modelName='jingyaogong/minimind2:latest'
    answer=getAnswer([c,c2,c3] )
    print(answer)
    isVisionModel=True
    answer=getAnswer([c,c2,c3] )
    print(answer)
    useOllama=False
    builtInLanguageModel=True
    answer=getAnswer([c,c2,c3] )
    print(answer)
    builtInLanguageModel=False
    server_url = 'http://localhost:8000/v1'
    API_KEY='21r234242'
    answer=getAnswer([c,c2,c3] )
    print(answer)

