import importlib
import configparser
import requests
import load
from colorama import Fore
import base64
import os
import requests
from typing import List, Optional

config = configparser.ConfigParser()
config.read('config.ini', encoding='utf-8')
modelName: str = config['general']['modelName']
server_url: str=config['general']['server_url']
isVisionModel: bool=config.getboolean('general', 'isVisionModel')


API_KEY=config['general']['API_KEY']


if API_KEY=='None':
    API_KEY=None
useOllama=False
ollama=None
MAX_LENGTH=300
if server_url=='Ollama':
    ollama=importlib.import_module('ollama')
    useOllama=True

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


import re
def _build_messages_OpenAI(
    text: str,
    system_prompt: str = '',
    image_paths: Optional[List[str]] = None,
    is_vision: bool = False
) -> List[dict]:
    messages = []
    
    # 添加系统消息（非空才加）
    if system_prompt:
        messages.append({"role": "system", "content": system_prompt})
    
    # 构建用户消息内容
    if is_vision and image_paths:
        user_content = [{"type": "text", "text": text}]
        for path in image_paths:
            if not os.path.isfile(path):
                raise FileNotFoundError(f"Image file not found: {path}")
            # Ollama 支持 file:// 协议
            file_url = f"file://{os.path.abspath(path).replace('\\', '/')}" # type: ignore
            user_content.append({ # type: ignore
                "type": "image_url",
                "image_url": {"url": file_url}
            })
        messages.append({"role": "user", "content": user_content})
    else:
        messages.append({"role": "user", "content": text})
    
    return messages

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
def getAnswer_(text: str,imageList=None):
    message=[
                {
                    'role': 'system',
                    'content': config.get('general', 'system') if config.get('general', 'system') != 'None' else ''
                },
                {
                    'role': 'user',
                    'content': text
                }
            ]
    if isVisionModel and imageList:
        message.append({
            'role': 'image',
            'content': imageList
        })
    
    if useOllama:
        response = ollama.chat( # type: ignore
            model=modelName,
            messages=message,
            stream=True
        )
        result = ''
        length=0
        for chunk in response:
            result += chunk['message']['content']
            length+=len(chunk['message']['content'])
            if length>=MAX_LENGTH:
                break
            print(chunk['message']['content'], end='')
        return result
    else:
        # 兼容 OpenAI 及类 OpenAI API 的通用调用
        headers = {
            "Authorization": f"Bearer {API_KEY}",
            "Content-Type": "application/json"
        }

        # 构建消息
        messages = message

        data = {
            "model": modelName,
            "messages": messages
        }

        try:
            response = requests.post(server_url, headers=headers, json=data, timeout=30)

            if response.status_code == 200:
                json_resp = response.json()
                # 大多数类 OpenAI 接口都返回 choices[0].message.content
                content = json_resp["choices"][0]["message"]["content"]
                return content[:MAX_LENGTH]
            else:
                print(f"API Error: {response.status_code} - {response.text}")
                return None
        except Exception as e:
            print(f"Request failed: {e}")
            return None
        
def getAnswer(text: str, imageList: Optional[List[str]] = None) -> Optional[str]:
    """
    调用 AI 模型获取回答（支持纯文本或图文输入）。
    
    Args:
        text: 用户问题文本
        imageList: 本地图像路径列表（仅 vision 模型有效）
    
    Returns:
        模型返回的文本，或 None（出错时）
    """
    # 获取系统提示
    system_prompt = config.get('general', 'system')
    if system_prompt == 'None':
        system_prompt = ''
    
    # 构建消息

    
    if useOllama:
        messages = []
        if system_prompt:
            messages.append({"role": "system", "text": system_prompt})
        if imageList and isVisionModel:
            messages.append({"role": "user", "content": text, "images": [os.path.abspath(p) for p in imageList if os.path.exists(p)]})
        else:
            messages.append({"role": "user", "content": text})
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
        messages = _build_messages_OpenAI(
            text=text,
            system_prompt=system_prompt,
            image_paths=imageList,
            is_vision=isVisionModel
        )
        # OpenAI 或兼容 API
        headers = {
            "Authorization": f"Bearer {API_KEY}",
            "Content-Type": "application/json"
        }
        data = {
            "model": modelName,
            "messages": messages,
            "max_tokens": MAX_LENGTH  # 推荐用 max_tokens 控制长度
        }
        
        try:
            response = requests.post(server_url, headers=headers, json=data, timeout=30)
            if response.status_code == 200:
                content = response.json()["choices"][0]["message"]["content"]
                return content.strip()
            else:
                print(f"API Error: {response.status_code} - {response.text}")
                return None
        except Exception as e:
            print(f"Request failed: {e}")
            return None
                
                

if __name__ == '__main__':
    answer=getAnswer('解释图片',[r'screenshot.png',r'conversation0.png'])
