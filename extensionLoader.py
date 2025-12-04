import importlib
import os
from colorama import Fore
from typing import List,Any
from chatContent import ChatContent
import logging
extensions=[]
extension_names=[]
warn=False
os.makedirs('Extensions',exist_ok=True)
for mod in os.listdir('Extensions'):
    if mod.endswith('.py'):
        if not warn:
            warn=True
            print(f"{Fore.YELLOW}随意加载扩展可能导致运行缓慢，报错，甚至有可能破坏文件{Fore.RESET}")
        print(f"正在加载\t{mod}",end='\r')
        try:
            extension_names.append(mod[:-3])
            extensions.append(importlib.import_module('Extensions.'+mod[:-3]))
            print(f"{Fore.GREEN}_已加载\t\t{mod}{Fore.RESET}")
        except Exception as e:
            print(f'{Fore.YELLOW}加载错误\t{mod}\t{e}{Fore.RESET}')

def callEveryExtension(func_name,*args,**kwargs)->Any:
    result=[]
    for mod_name,mod in zip(extension_names,extensions):
        try:
            func=getattr(mod,func_name)
            result.append(func(*args,**kwargs))
            logging.debug(f'{mod_name}.{func_name}',args,kwargs)
        except Exception as e:
            logging.debug(f'{e}:{mod_name}.{func_name}',exc_info=True)
    new_result=[i for i in result if i is not None]
    return new_result if len(new_result)>0 else None
if __name__=='__main__':
    callEveryExtension('after_receiving_messages',[ChatContent('',[],'','',True)])
    callEveryExtension('after_screenshot')
    callEveryExtension('before_sending_the_message_by_AI_generated','1')
    callEveryExtension('after_screenshot')

# def after_receiving_messages(messages: List[ChatContent]) -> None:
#     # 信息被处理后调用
#     # 参数
#     # messages : 收到的信息
#     pass

# def before_sending_the_message_by_AI_generated(answer:str) -> str:
#     # 信息被发送前调用
#     # 参数
#     # answer : 获取的答案
#     # 返回值
#     # 对答案的修改,直接返回答案则无修改
#     # 必须有返回值
#     return answer

# def after_screenshot() -> None:
#     # 截图后调用
#     # 截图保存在当前目录下的screenshot.bmp
#     pass


# for mod_name,mod in zip(mod_names,mods):
#     print(mod_name)
#     print(mod.description)
#     mod.after_receiving_messages(None)
#     mod.after_screenshot()
#     mod.before_sending_the_message_by_AI_generated('')
    

