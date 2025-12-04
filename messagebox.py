import ctypes

MB_OK = 0x0
MB_OKCANCEL = 0x1
MB_YESNO = 0x4
MB_ICONINFO = 0x40
MB_ICONWARN = 0x30
MB_ICONERROR = 0x10
MB_ICONQUESTION = 0x20

def MessageBox(text, title="提示", style=MB_OK | MB_ICONINFO):
    return ctypes.windll.user32.MessageBoxW(0, text, title, style)

# 使用
if __name__ == "__main__":
    MessageBox("你好，世界！")
    if MessageBox("继续吗？", "确认", MB_YESNO | MB_ICONQUESTION) == 6:
        print("用户点了 是")