import pyautogui
from time import sleep

pyautogui.moveTo(2151, 852)
pyautogui.mouseDown(button='left')
pyautogui.moveTo(435,0, duration=.1)
sleep(4)
pyautogui.mouseUp(button='left')

pyautogui.click(1711,1048)
import pyperclip
sleep(2)
result=pyperclip.paste()
print(result)
print('===========================')
from conversationStyleExtract import extract

for i in extract(result):
    print(i.report())

