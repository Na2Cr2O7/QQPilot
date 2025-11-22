MAX_IMAGES_COUNT = 2 # 减少服务器token请求次数或者计算机负担，限制图片数量2张


import configparser
from typing import List
from datetime import datetime
import os
import logging

logging.basicConfig(level=logging.DEBUG, format='%(asctime)s - %(name)s - %(levelname)s - %(message)s')
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
    global existingFiles
    logging.debug("findImageBegin")
    existingFiles = _listAllFiles()
    logging.debug(existingFiles)
    

def findImageEnd() -> List[str]:
    global existingFiles
    newFiles: List[str] = _listAllFiles()
    newFiles = list(set(newFiles) - set(existingFiles))
    logging.debug(f"newFiles: {newFiles}")
    print(f"newFiles: {newFiles}")
    return newFiles[:MAX_IMAGES_COUNT]
if __name__ == '__main__':
    findImageBegin()
    input("Press Enter to continue...")
    newFiles = findImageEnd()
    print(newFiles)

