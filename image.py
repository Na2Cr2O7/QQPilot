import ctypes
from ctypes import Structure, c_int, c_uint, c_void_p, POINTER
import os
import configparser
config = configparser.ConfigParser()
config.read('config.ini',encoding='utf-8')
width=config.getint('general', 'width')
height=config.getint('general', 'height')
scale=config.getfloat('general', 'scale')

# 定义 Point 结构体
class Point(Structure):
    _fields_ = [
        ("x", c_uint),
        ("y", c_uint)
    ]

    def __repr__(self):
        return f"Point(x={self.x}, y={self.y})"

    def is_null(self):
        return self.x == 0 and self.y == 0


# 定义 RECT 结构体（注意：Windows API 中 RECT 是 left/top/right/bottom）
class RECT(Structure):
    _fields_ = [
        ("left", c_uint),
        ("top", c_uint),
        ("right", c_uint),
        ("bottom", c_uint)
    ]

    def __repr__(self):
        return f"RECT(left={self.left}, top={self.top}, right={self.right}, bottom={self.bottom})"


dll = ctypes.CDLL(os.path.abspath('Vimage.dll'))  # 或使用 ctypes.WinDLL 如果是 stdcall

# 函数1: screenshot
dll.screenshot.argtypes = [c_int, c_int, c_int, c_int]
dll.screenshot.restype = c_int  # 返回 1 表示失败

dll.fullScreenshot.argtypes = []
dll.fullScreenshot.restype = c_int

# 函数2: containsRedDot
dll.containsRedDot.argtypes = [RECT]
dll.containsRedDot.restype = Point

# 函数3: containsBlue
dll.containsBlue.argtypes = []
dll.containsBlue.restype = Point

# 函数4: point（构造 Point）
dll.point.argtypes = [c_uint, c_uint]
dll.point.restype = Point

# 函数5: rect（构造 RECT）
dll.rect.argtypes = [c_uint, c_uint, c_uint, c_uint]
dll.rect.restype = RECT
# print(0, 0, int(width*scale), int(height*scale))
# # 截图
# result = dll.screenshot(0, 0, int(width*scale), int(height*scale))
# if result == 1:
#     print("截图失败")
# else:
#     print("截图成功")

# # 构造一个区域
# r = dll.rect(100, 100, 300, 300)

# # 检查红点
# red_point = dll.containsRedDot(r)
# if red_point.is_null():
#     print("没有红点")
# else:
#     print("红点位置:", red_point)

# # 检查蓝色按钮
# blue_point = dll.containsBlue()
# if blue_point.is_null():
#     print("没有蓝色按钮")
# else:
#     print("蓝色按钮位置:", blue_point)
def rect(x, y, width, height):
    return dll.rect(x, y, width, height)
def point(x, y):
    return dll.point(x, y)
def screenshot(x, y, width, height):
    result = dll.screenshot(x, y, width, height)
    return not result == 1
def fullScreenShot():
    result = dll.fullScreenshot()
    return not result == 1
def containsRedDot(rect):
    point=dll.containsRedDot(rect)
    return [point.x, point.y]


def containsBlue():
    point=dll.containsBlue()

    return [point.x, point.y]

if __name__ == '__main__':
    print(fullScreenShot())
    print(dll.rect(0, 0, int(width*scale),int(height*scale)))
    print(containsRedDot(dll.rect(0, 0, int(width*scale),int(height*scale))))
    # print(containsBlue())
    # print(screenshot(0, 0, int(1920*scale),int(1080*scale)))