
from PIL import Image, ImageDraw
# paddleOCR

from paddleocr import PaddleOCR
import os

ocr=PaddleOCR(
   use_doc_orientation_classify=False, 
    use_doc_unwarping=False,)
def getAllTextWithBoxesDrawn(imagePath:str):
    result=ocr.predict(os.path.abspath(imagePath))
    for line in result:
        print(line)


if __name__ == '__main__':
    getAllTextWithBoxesDrawn('1695619823634e97274c6343b5d6bd3f5f115ac082db0bac679f48f7a8694b473ade98fc07b4e.0.jpg')







