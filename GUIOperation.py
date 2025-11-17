import pyautogui
import pytweening
import pyperclip

import time

def click(x: int, y: int):
    print(x,y)
    pyautogui.moveTo(x, y,duration=1, tween=pytweening.easeInOutQuad)
    pyautogui.click()
def goto(x: int, y: int):
    pyautogui.moveTo(x, y,duration=1, tween=pytweening.easeInOutQuad)
def scrollUp(length: int = 120):
    for i in range(4):
        pyautogui.scroll(length)
        time.sleep(.1)
def scrollDown(length: int = 120):
    for i in range(4):
        pyautogui.scroll(-length)
        time.sleep(.1)
def sendTextWithoutClick(text:str):
    temp=''
    for i in text:
        if i=='\n':
            pyperclip.copy(temp)
            time.sleep(.2)
            temp=''
            pyautogui.hotkey('ctrl', 'v')
            pyautogui.press('enter')
            continue
        temp+=i
    pyperclip.copy(temp)
    time.sleep(.2)
    pyautogui.hotkey('ctrl', 'v')


import ctypes
import os
def uploadFile():
    dll=ctypes.CDLL(os.path.abspath('uploadFile.dll'))
    # extern "C" int __declspec(dllexport) upload()
    dll.upload()
    print('\n')

import ocr
def clickText(imagePath:str, text:str) -> bool:
    result=ocr.OCR(imagePath)
    for i in result:
        if text in i[1]: # type: ignore
            pos1,pos2,pos3,pos4=i[0]  # type: ignore
            x=[pos1[0],pos2[0],pos3[0],pos4[0]]
            y=[pos1[1],pos2[1],pos3[1],pos4[1]]
            x.sort()
            y.sort()
            click(int(x[1]),int(y[1])) 
            return True
    return False
def clickTexts(imagePath:str, text:str) -> bool:
    result=ocr.OCR(imagePath)
    success=False
    for i in result:
        if text in i[1]: # type: ignore
            pos1,pos2,pos3,pos4=i[0]  # type: ignore
            x=[pos1[0],pos2[0],pos3[0],pos4[0]]
            y=[pos1[1],pos2[1],pos3[1],pos4[1]]
            minX=int(min(x))
            maxX=int(max(x))
            minY=int(min(y))
            maxY=int(max(y))

            click((minX+maxX)//2, (minY+maxY)//2) 
            success=True
    return success

import subprocess
import ctypes

# def focus():
#     subprocess.run('focusqqwindow.exe')
def focus():
    dll=ctypes.CDLL(os.path.abspath('FocusQQWindow2.dll'))
    # extern "C" int __declspec(dllexport) focus()
    dll.focus()
if __name__ == '__main__':
    while True: 
        input("Press Enter to continue...")
        focus()


