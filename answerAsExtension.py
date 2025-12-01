# answerAsExtension.py
# 用于可能的二次开发

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


def getAnswer(text:list[ChatContent]) -> Optional[str]:
    '''
        获取收到的问题，图片等
    '''
    textList=[]
    imageList=[]
    for chat in text:
        print(chat.report())
        textList.append(chat.text)
        if isVisionModel:
            for i in chat.imagePaths:
                if os.path.exists(i):
                    imageList.append(i)
    print(textList,imageList)


                

