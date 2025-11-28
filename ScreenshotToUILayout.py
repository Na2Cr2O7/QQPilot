from colorama import Fore
import load
load.startLoading(Fore.GREEN,"正在初始化")

from typing import Any, Generator, Literal
from random import randint
import subprocess


import image

import logging
logging.basicConfig(level=logging.INFO,format='%(asctime)s [%(levelname)s] %(message)s',datefmt='%Y-%m-%d %H:%M:%S')


import time
import configparser
from conversationStyleExtract import * 

import threading


import positions
import answer
# import enhance
import pyperclip

from GUIOperation import *
        

    


load.stopLoading()

logging.info(f"{Fore.GREEN}初始化完成{Fore.RESET}")

# def containsRedDot(image: Image.Image):
#     size=image.size
#     RED_DOT_COLOR=(247,76,48)
#     for x in range(size[0]):
#         for y in range(size[1]):
#             pixel=image.getpixel((x,y))
#             if pixel==RED_DOT_COLOR:
#                 return (x,y)
#     return False
# def containsBlue(image: Image.Image):
#     BLUE=(0, 153, 255)
#     for x in range(0,image.width,10):
#         for y in range(0,image.height,10):
#             pixel=image.getpixel((x,y))
#             if pixel==BLUE:
#                 yield (x,y)
#     return False
# def screenshot(positionRect: tuple[int, int, int, int]) -> Image.Image:
#     logging.debug(f"screenshotting {ImageGrab.grab(bbox=positionRect)}")
#     return ImageGrab.grab(bbox=positionRect)
# logging.info(f"{Fore.GREEN}准备开始运行{Fore.RESET}")

autoFocusShouldRun=True
def autoFocus():
    global autoFocusShouldRun
    while autoFocusShouldRun:
        focus()
        logging.debug("Focusing...")
        time.sleep(4)

t=None

if __name__ == '__main__':
    try:
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
        sendImagePossibility=config.get('general','sendImagePossibility')
        isVisionModel=config.getboolean('general','isVisionModel')

        print(f"{Fore.YELLOW}{config.get('general','version')}{Fore.RESET}")
        sendImagePossibility=int(sendImagePossibility)


        if autoFocusing=='True':
            logging.info("自动聚焦功能已开启")
            t=threading.Thread(target=autoFocus)
            t.start()
        if autoLogin=='True':
            logging.info("自动登录功能已开启")
            logging.info("正在尝试登录...")
            for _ in range(4):

                image.fullScreenShot()
                i=image.containsBlue()
                if i==[0,0]:
                    time.sleep(1)
                    continue
                click(*i)
                time.sleep(2)
            time.sleep(1)
                
            



        
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

        copyButtonActualSize: tuple[int, int, int, int]=positions.toActualSize(positions.COPY_BUTTON_BBOX_RELATIVE_SIZE,size)
        logging.debug(f"复制按钮实际大小: {copyButtonActualSize}")

        startDraggingAbsolutePosition=positions.toActualPoint(positions.START_DRAGGING_RELATIVE_POSITION,size)
        endDraggingAbsolutePosition=positions.toActualPoint(positions.END_DRAGGING_RELATIVE_POSITION,size)
        logging.debug(f"开始拖拽位置: {startDraggingAbsolutePosition}")
        logging.debug(f"结束拖拽位置: {endDraggingAbsolutePosition}")

        while True:
            try:
                # im=image.screenshot(*positionRect)
                
                # im.save("screenshot.png")
                # chatList: Image.Image=im.crop(chatListActualSize)
                chatList=image.fullScreenShot()

                # del im

                contain=image.containsRedDot(image.rect(*chatListActualSize))
                print(contain)
                if contain!=[0,0]:
                    logging.info(f"发现红点: {contain}")

                    click(contain[0],contain[1])
                    time.sleep(2)
                    

                    conversationText=[]
                    dragFromTo(*startDraggingAbsolutePosition,*endDraggingAbsolutePosition)

                    #七次tab找到复制按钮
                    for i in range(7):
                        tab()
                        time.sleep(.1)
                    pyautogui.press('enter')

                    
                    time.sleep(4)
                    
                    CharContents=extract(pyperclip.paste())
                    images=[]
                    for text in CharContents:
                        for imagePath in text.imagePaths:
                            if os.path.exists(imagePath):
                                images.append(imagePath)
                    conversationText=[str(text) for text in CharContents]
                    
                    #send answer
                    click(commentSectionActualSize[0]+((commentSectionActualSize[2]-commentSectionActualSize[0])//2),commentSectionActualSize[1]+((commentSectionActualSize[3]-commentSectionActualSize[1])//2))



                    print(f"{Fore.CYAN}{'\n'.join(list(conversationText))}{Fore.RESET}")
                    if isVisionModel and images:
                        result=answer.getAnswer(CharContents,images)
                    else:
                        result=answer.getAnswer(CharContents)
                    
                    if type(result)==str:
                        result+=indentificationString
                        # logging.info(f"{Fore.GREEN}回答: {result}{Fore.RESET}")
                        sendTextWithoutClick(result)

                    # upload image
                    if withImage and randint(0,99)<sendImagePossibility:
                        
                        logging.info("上传图片")

                        subprocess.run(['uploadImage2.exe'])

                        # click(sendImageActualSize[0]+((sendImageActualSize[2]-sendImageActualSize[0])//2),sendImageActualSize[1]+((sendImageActualSize[3]-sendImageActualSize[1])//2))

                        # time.sleep(6)

                        # uploadFile()
                        # time.sleep(2)


                    # click "send" button
                    logging.info("发送消息")
                    pyautogui.hotkey('ctrl','enter')
                    # click(sendButtonActualSize[0]+((sendButtonActualSize[2]-sendButtonActualSize[0])//2)
                    #         ,sendButtonActualSize[1]+((sendButtonActualSize[3]-sendButtonActualSize[1])//2))
                    
                    time.sleep(.1)

                    # exit conversation
                    logging.info("退出会话")
                    click(contain[0],contain[1])
                # else:
                #     if isVisionModel:
                #         conversationImages.findImageBegin()
                else:
                    time.sleep(2) # 防止截图过快对硬盘损伤大
            except KeyboardInterrupt:
                logging.error(f"{Fore.RED}KeyboardInterrupt{Fore.RESET}")
                autoFocusShouldRun=False
                raise SystemExit
                if t:
                    t.join()
    except KeyboardInterrupt:
        logging.error(f"{Fore.RED}KeyboardInterrupt{Fore.RESET}")
        autoFocusShouldRun=False
        raise SystemExit
        if t:
            t.join()
        

