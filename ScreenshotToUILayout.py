from colorama import Fore
import load
import dockLog
load.startLoading(Fore.GREEN,"正在初始化")
floatingTextApp=dockLog.start_floating_window()
dockLog.setText("正在初始化-按右键关闭浮窗")
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
        

import extensionLoader


load.stopLoading()

logging.info(f"{Fore.GREEN}初始化完成{Fore.RESET}")
dockLog.setText("初始化完成")


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
        ATDetect=config.getboolean('general','ATDetect')

        print(f"{Fore.YELLOW}{config.get('general','version')}{Fore.RESET}")
        sendImagePossibility=int(sendImagePossibility)


        if autoFocusing=='True':
            logging.info("自动聚焦功能已开启")
            t=threading.Thread(target=autoFocus)
            t.start()
        if autoLogin=='True':
            logging.info("自动登录功能已开启")
            logging.info("正在尝试登录...")
            dockLog.setText("正在尝试登录...")
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


        atPlaceActualSize: tuple[int, int, int, int]=positions.toActualSize(positions.AT_PLACE_BBOX_RELATIVE_SIZE,size)
        logging.debug(f"@位置实际大小: {atPlaceActualSize}")

        startDraggingAbsolutePosition=positions.toActualPoint(positions.START_DRAGGING_RELATIVE_POSITION,size)
        endDraggingAbsolutePosition=positions.toActualPoint(positions.END_DRAGGING_RELATIVE_POSITION,size)
        logging.debug(f"开始拖拽位置: {startDraggingAbsolutePosition}")
        logging.debug(f"结束拖拽位置: {endDraggingAbsolutePosition}")


        cancelButtonActualPosition=positions.toActualPoint(positions.CANCEL_BUTTON_RELATIVE_POSITION,size)
        while True:
            try:
                # im=image.screenshot(*positionRect)
                
                # im.save("screenshot.png")
                # chatList: Image.Image=im.crop(chatListActualSize)
                chatList=image.fullScreenShot()

                extensionLoader.callEveryExtension("after_screenshot")

                # del im
                if ATDetect:
                    contain=image.containsRedDot(image.rect(*atPlaceActualSize))
                else:
                    contain=image.containsRedDot(image.rect(*chatListActualSize))   
                if contain!=[0,0]:
                    dockLog.setText("🚫🖱️发现新信息  ")
                    logging.info(f"发现红点: {contain}")

                    click(contain[0],contain[1])
                    time.sleep(2)
                    

                    conversationText=[]
                    
                    dragFromTo(*startDraggingAbsolutePosition,*endDraggingAbsolutePosition)


                    #七次tab找到复制按钮
                    dockLog.setText("🚫🖱️ 请勿移动鼠标")
                    time.sleep(.1)
                    goto(conversationActualSize[0]+((conversationActualSize[2]-conversationActualSize[0])//2),conversationActualSize[1]+((conversationActualSize[3]-conversationActualSize[1])//2))
                    
                    for i in range(scrollTries):
                        scrollDown()

                    for i in range(7):
                        tab()
                        time.sleep(.2)
                    pyautogui.press('enter')

                    
                    
                    time.sleep(2)
                    
                    click(cancelButtonActualPosition[0],cancelButtonActualPosition[1])

                    ChatContents=extract(pyperclip.paste())

                    ChatContentsList=extensionLoader.callEveryExtension("after_receiving_messages",ChatContents) 
                    ChatContents=[]
                    for i in ChatContentsList:  # type: ignore 
                        ChatContents+=i


                    images=[]
                    for text in ChatContents:  # type: ignore 
                        for imagePath in text.imagePaths:
                            if os.path.exists(imagePath):
                                images.append(imagePath)
                    # conversationText=[str(text) for text iChatContentsts]
                    
                    dockLog.setText("🚫🖱️等待语言模型生成答案")
                    #send answer
                    click(commentSectionActualSize[0]+((commentSectionActualSize[2]-commentSectionActualSize[0])//2),commentSectionActualSize[1]+((commentSectionActualSize[3]-commentSectionActualSize[1])//2))



                    print(f"{Fore.CYAN}{'\n'.join(list(conversationText))}{Fore.RESET}")
                    try:
                        result=answer.getAnswer(ChatContents)
                    except Exception as e:
                        logging.error(f"语言模型生成答案失败\n{e}")
                        dockLog.setText("× 语言模型生成答案失败")
                        result=""
                    
                    result=extensionLoader.callEveryExtension("before_sending_the_message_by_AI_generated",result)

                    click(commentSectionActualSize[0]+((commentSectionActualSize[2]-commentSectionActualSize[0])//2),commentSectionActualSize[1]+((commentSectionActualSize[3]-commentSectionActualSize[1])//2))
                    
                    if type(result)==str:
                        result+=indentificationString
                        # logging.info(f"{Fore.GREEN}回答: {result}{Fore.RESET}")
                        sendTextWithoutClick(result)

                    # upload image
                    if withImage and randint(0,99)<sendImagePossibility:
                        
                        logging.info("上传图片")
                        dockLog.setText("🚫⌨️ 正在上传图片...")

                        subprocess.run(['uploadImage2.exe'])
                        time.sleep(.2)
                        pyautogui.hotkey('ctrl','v')

                        # click(sendImageActualSize[0]+((sendImageActualSize[2]-sendImageActualSize[0])//2),sendImageActualSize[1]+((sendImageActualSize[3]-sendImageActualSize[1])//2))

                        time.sleep(6)

                        # uploadFile()
                        # time.sleep(2)


                    # click "send" button
                    logging.info("发送消息")
                    pyautogui.hotkey('ctrl','enter')
                    dockLog.setText("发送消息 🎉")
                    # click(sendButtonActualSize[0]+((sendButtonActualSize[2]-sendButtonActualSize[0])//2)
                    #         ,sendButtonActualSize[1]+((sendButtonActualSize[3]-sendButtonActualSize[1])//2))
                    
                    time.sleep(.1)

                    # exit conversation
                    logging.info("退出会话")
                    click(chatListActualSize[0]+int(100*scale),chatListActualSize[1]+int(20*scale))
                # else:
                #     if isVisionModel:
                #         conversationImages.findImageBegin()
                else:
                    time.sleep(2) # 防止截图过快对硬盘损伤大
                    dockLog.setText("正在寻找新信息...")
            except KeyboardInterrupt:
                logging.error(f"{Fore.RED}KeyboardInterrupt{Fore.RESET}")
                autoFocusShouldRun=False
                raise SystemExit
                if t:
                    t.join()
    except KeyboardInterrupt:
        logging.error(f"{Fore.RED}KeyboardInterrupt{Fore.RESET}")
        dockLog.stop_floating_window()
        
        autoFocusShouldRun=False
        raise SystemExit
        if t:
            t.join()
        

