
import configparser
config = configparser.ConfigParser()
config.read('config.ini',encoding='utf-8')
width=config.getint('general', 'width')
height=config.getint('general', 'height')
scale=config.getfloat('general', 'scale')
from PIL import Image
from PIL import ImageGrab
SCREENSHOT_NAME='screenshot.png'
class RECT(object):
    left = 0
    top = 0
    right = 0
    bottom = 0
    def __init__(self, left, top, right, bottom):
        self.left = left
        self.top = top
        self.right = right
        self.bottom = bottom
def rect(x, y, width, height):
    return RECT(x,y,width+x,height+y)
def screenshot(x, y, width, height):
    img =  ImageGrab.grab()
    img = img.crop((x, y, x + width, y + height))
    img.save(SCREENSHOT_NAME)
    return img
def fullScreenShot():
    img = ImageGrab.grab()
    img.save(SCREENSHOT_NAME)
    return img

def containsRedDot(rect):
    RED_DOT=(247,76,48)
    image=Image.open(SCREENSHOT_NAME)
    width=image.width
    height=image.height
    for x in range(rect.left,rect.right):
        for y in range(rect.top,rect.bottom):
            pixel=image.getpixel((x,y))
            if pixel==RED_DOT:
                return [x,y]
    return [0,0]

def containsBlue():
    BLUE=(0,153,255)
    fullScreenShot()
    image=Image.open(SCREENSHOT_NAME)
    width=image.width
    height=image.height
    for x in range(width):
        for y in range(height):
            pixel=image.getpixel((x,y))
            if pixel==BLUE:
                return [x,y]
    return [0,0]


