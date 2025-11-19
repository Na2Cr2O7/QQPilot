from typing import Any, Generator, Literal

from PIL import ImageGrab, Image,ImageDraw

from colorama import Fore

import logging
logging.basicConfig(level=logging.INFO,format='%(asctime)s [%(levelname)s] %(message)s',datefmt='%Y-%m-%d %H:%M:%S')


from PIL.ImageFile import ImageFile

import time
import configparser

import numpy as np
import threading


import positions
import answer
import enhance
logging.debug("importing ocr")
import ocr

from GUIOperation import click,goto,scrollUp,scrollDown,sendTextWithoutClick,uploadFile,focus,clickTexts
        

    


def containsRedDot(image: Image.Image):
    size=image.size
    RED_DOT_COLOR=(247,76,48)
    for x in range(size[0]):
        for y in range(size[1]):
            pixel=image.getpixel((x,y))
            if pixel==RED_DOT_COLOR:
                return (x,y)
    return False
def screenshot(positionRect: tuple[int, int, int, int]) -> Image.Image:
    logging.debug(f"screenshotting {ImageGrab.grab(bbox=positionRect)}")
    return ImageGrab.grab(bbox=positionRect)
logging.info(f"{Fore.GREEN}准备开始运行{Fore.RESET}")

autoFocusShouldRun=True
def autoFocus():
    global autoFocusShouldRun
    while autoFocusShouldRun:
        focus()
        logging.debug("Focusing...")
        time.sleep(4)


if __name__ == '__main__':
    focus()
    time.sleep(1)

    config=configparser.ConfigParser()
    config.read('config.ini',encoding='utf-8')
    size: tuple[int, int]=int(config.get('general','width')),int(config.get('general','height'))

    scale=float(config.get('general','scale'))
    scrollTries=int(config.get('general','scroll'))
    withImage=config.get('general','withImage')
    autoLogin=config.get('general','autoLogin')
    autoFocusing=config.get('general','autoFocusing')
    t=None

    if autoFocusing=='True':
        logging.info("自动聚焦功能已开启")
        t=threading.Thread(target=autoFocus)
        t.start()
    if autoLogin=='True':
        logging.info("自动登录功能已开启")
       

        while True:
            isLogin=False
            for i in range(4):
                logging.info("正在尝试登录...")
                ImageGrab.grab().save('login.png')
                if clickTexts('login.png',"登录"):
                    isLogin=True
                    break
                time.sleep(1)
            if isLogin:
                break
            if input(f"{Fore.RED}如果已经登录，请输入'A'继续,否则按回车继续登录:{Fore.RESET}").capitalize()=='A':
                break



    
    if withImage=='True':
        withImage=True
    else:
        withImage=False

    
    
    size=(int(size[0]*scale),int(size[1]*scale))

    logging.debug(f"size with scale: {size}, scale: {scale}")



    positionRect: tuple[Literal[0], Literal[0], int, int]=(0,0,*size)


    logging.debug(f"QQ窗口位置: {positionRect}")

    chatListActualSize: tuple[int, int, int, int]=positions.toActualSize(positions.CHAT_LIST_BBOX_RELATIVE_SIZE,size)
    logging.debug(f"聊天列表实际大小: {chatListActualSize}")

    conversationActualSize: tuple[int, int, int, int]=positions.toActualSize(positions.CONVERSATION_BBOX_RELATIVE_SIZE,size)
    logging.debug(f"聊天区域实际大小: {conversationActualSize}")

    commentSectionActualSize: tuple[int, int, int, int]=positions.toActualSize(positions.COMMENT_SECTION_BBOX_RELATIVE_SIZE,size)
    logging.debug(f"输入框实际大小: {commentSectionActualSize}")

    sendButtonActualSize: tuple[int, int, int, int]=positions.toActualSize(positions.SEND_BUTTON_BBOX_RELATIVE_SIZE,size)
    logging.debug(f"发送按钮实际大小: {sendButtonActualSize}")

    exitConversationActualSize: tuple[int, int, int, int]=positions.toActualSize(positions.EXIT_CONVERSATION_BBOX_RELATIVE_SIZE,size)
    logging.debug(f"退出会话按钮实际大小: {exitConversationActualSize}")

    sendImageActualSize: tuple[int, int, int, int]=positions.toActualSize(positions.SEND_IMAGE_BBOX_RELATIVE_SIZE,size)
    logging.debug(f"发送图片按钮实际大小: {sendImageActualSize}")


    while True:
        try:
            im=screenshot(positionRect)
            im.save("screenshot.png")
            chatList: Image.Image=im.crop(chatListActualSize)
            del im

            contain: tuple[int, int] | Literal[False]=containsRedDot(chatList)

            if contain :
                logging.info(f"发现红点: {contain}")

                click(contain[0]+chatListActualSize[0],contain[1]+chatListActualSize[1])
                time.sleep(2)
                

                # conversation
                goto(conversationActualSize[0]+((conversationActualSize[2]-conversationActualSize[0])//2),conversationActualSize[1]+((conversationActualSize[3]-conversationActualSize[1])//2))
                for _ in range(scrollTries):
                    scrollUp()
                conversationText=set()
                for scrollTry in range(scrollTries):
                    
                    im=screenshot(positionRect)
                    

                    conversation=im.crop(conversationActualSize)
                    del im

                    # conversationTexts=getAllTextWithBoxesDrawn("conversation.png")
                    # print(conversationTexts)
                    fn=f"conversation{scrollTry}.png"
                    conversation.save(fn)


                    conversation=enhance.getConversation(fn)


                    for i in ocr.getAllTextWithBoxesDrawn(conversation):
                        conversationText.add(i)
                    scrollDown()

                
                #send answer
                click(commentSectionActualSize[0]+((commentSectionActualSize[2]-commentSectionActualSize[0])//2),commentSectionActualSize[1]+((commentSectionActualSize[3]-commentSectionActualSize[1])//2))


                logging.info(f"{Fore.CYAN}{'\n'.join(list(conversationText))}{Fore.RESET}")

                result=answer.getAnswer('\n'.join(list(conversationText)))
                
                if type(result)==str:
                    logging.info(f"{Fore.GREEN}回答: {result}{Fore.RESET}")
                    sendTextWithoutClick(result)

                # upload image
                if withImage:

                    logging.info("上传图片")
                    click(sendImageActualSize[0]+((sendImageActualSize[2]-sendImageActualSize[0])//2),sendImageActualSize[1]+((sendImageActualSize[3]-sendImageActualSize[1])//2))

                    time.sleep(6)

                    uploadFile()
                    time.sleep(2)


                # click "send" button
                logging.info("发送消息")
                click(sendButtonActualSize[0]+((sendButtonActualSize[2]-sendButtonActualSize[0])//2)
                        ,sendButtonActualSize[1]+((sendButtonActualSize[3]-sendButtonActualSize[1])//2))
                
                time.sleep(.1)

                # exit conversation
                logging.info("退出会话")
                click(exitConversationActualSize[0],exitConversationActualSize[1])
        except KeyboardInterrupt:
            logging.error(f"{Fore.RED}KeyboardInterrupt{Fore.RESET}")
            autoFocusShouldRun=False
            if t:
                t.join()

