# 用于从NT数据目录中查找图片并复制到当前目录
# 使用方法：
# 先调用findImageBegin()函数，清空原有图片
# 然后调用findImageEnd()函数，查找新图片并复制到当前目录
import configparser
config = configparser.ConfigParser()
config.read('config.ini', encoding='utf-8')
MAX_IMAGES_COUNT: int = config.getint('general','maxImageCount') # 减少服务器token请求次数或者计算机负担，限制图片数


import configparser
from typing import List
from datetime import datetime
import os
import logging

logging.basicConfig(level=logging.DEBUG, format='%(asctime)s - %(name)s - %(levelname)s - %(message)s')
logging.debug(f"MAX_IMAGES_COUNT: {MAX_IMAGES_COUNT}")
from PIL import Image
unsupported=[".gif",".webp"]

def isImageValid(filePath: str):
    try:
        x=Image.open(filePath)
        x.save(os.path.splitext(filePath)[0]+".jpg")
        logging.debug(f"valid image: {filePath}")
        return os.path.splitext(filePath)[0]+".jpg"
    except:
        logging.error(f"invalid image: {filePath}")
        return False
    

def resizeImage(filePath: str, scale: float = 0.5) -> bool:
    try:    
        img = Image.open(filePath)
        img = img.resize((int(img.size[0]*scale), int(img.size[1]*scale)))
        img.save(filePath)
        logging.debug(f"resize image: {filePath}")
        return True
    except:
        logging.error(f"resize image failed: {filePath}")
        return False
    

def dateTimeString():
    return datetime.now().strftime("%Y-%m")

IMAGE_PATH1: str=r'Emoji\emoji-recv\\'+dateTimeString()+'\\Ori\\'
IMAGE_PATH2: str=r'Pic\\'+dateTimeString()+'\\Ori\\'

config = configparser.ConfigParser()
config.read('config.ini', encoding='utf-8')

initialImagePath: str = config['general']['nt_data']
imagePaths=[os.path.join(initialImagePath,IMAGE_PATH1),os.path.join(initialImagePath,IMAGE_PATH2)]

existingFiles: List[str] = []
def _listAllFiles() -> List[str]:
    files=[]
    for imagePath in imagePaths:
        if os.path.exists(imagePath):
            files += [os.path.join(imagePath, file) for file in os.listdir(imagePath)]

    return files

def findImageBegin():
    logging.debug("findImageBegin")
    files=_listAllFiles()
    for file in files:
        os.remove(file)
        logging.debug(f"remove file: {file}")
    
    logging.debug(existingFiles)
    

def findImageEnd() -> List[str]:
    global existingFiles
    newFiles: List[str] = _listAllFiles()
    newFiles = list(set(newFiles) - set(existingFiles))
    logging.debug(f"newFiles: {newFiles}")
    print(f"newFiles: {newFiles}")
    newFiles2=[]
    for file in newFiles:
        if os.path.exists(file):
            x=isImageValid(file)
            if not x:
                os.remove(file)
                logging.debug(f"remove file: {file}")
                continue
            newFiles2.append(x)
            print(os.path.basename(x)) # type: ignore
    return newFiles2[:MAX_IMAGES_COUNT]

def removeImages(files: List[str]):
    for file in files:
        os.remove(file)
        logging.debug(f"remove file: {file}")

if __name__ == '__main__':
    newFiles = findImageEnd()