import tkinter as tk
import threading
import queue
import time
from tkinter import font

import ctypes
awareness = ctypes.c_int()
errorCode = ctypes.windll.shcore.GetProcessDpiAwareness(0, ctypes.byref(awareness))
# print(awareness.value)
errorCode = ctypes.windll.shcore.SetProcessDpiAwareness(1)
if errorCode!= 0:
    print("SetProcessDpiAwareness failed with error code %d" % errorCode)



class FloatingTextApp:
    def __init__(self):
        self.root = None
        self.window = None
        self.display_text = None
        self.message_queue = queue.Queue()
        self.running = False
        
    def create_window(self):
        """创建悬浮窗口"""
        self.root = tk.Tk()
        self.root.title("调试")
        
        # 设置窗口属性 - 去掉标题栏，置顶显示
        self.root.overrideredirect(True)  # 去掉窗口边框
        self.root.attributes('-topmost', True)  # 置顶
        
        # 设置半透明背景（可选）
        self.root.attributes('-alpha', 0.7)
        
        # 窗口大小
        window_width = 600
        window_height = 80
        
        # 获取屏幕尺寸
        screen_width = self.root.winfo_screenwidth()
        screen_height = self.root.winfo_screenheight()
        
        # 计算右下角位置（留出20像素边距）
        x = screen_width - window_width - 20
        y = screen_height - window_height - 20
        
        self.root.geometry(f"{window_width}x{window_height}+{x}+{y}")
        
        # 设置背景颜色
        self.root.configure(bg="#181818")
        
        # 创建窗口（模拟）
        container = tk.Frame(
            self.root, 
            bg="#242424", 
            # relief=tk.FLAT, 
            padx=5, 
            pady=10
        )
        container.place(relx=0.5, rely=0.5, anchor='center', relwidth=0.9, relheight=0.8)
        
        # 创建文字标签
        self.display_text = tk.Label(
            container,
            text="VisionQQ",
            font=("微软雅黑", 11, "bold"),
            bg='#242424',
            fg='#ecf0f1',
            # wraplength=1000,
            # justify=tk.CENTER
        )
        self.display_text.pack(expand=True)

        
        
        self.root.bind('<Button-3>', self.on_right_click)  # 右键关闭
        
        # print(f"✨ 浮窗已创建，位置: ({x}, {y})")
        
    def on_right_click(self, event):
        """右键点击关闭窗口"""
        self.running = False
        self.root.quit()
        
        
    def run(self):
        """运行窗口主循环"""
        self.running = True
        self.create_window()
        
        
        try:
            while self.running:
                # 处理队列中的消息
                try:
                    # 非阻塞获取消息，超时100ms
                    message = self.message_queue.get(timeout=0.1)
                    if message == "STOP":
                        break
                    self.update_text(message)
                    self.message_queue.task_done()
                except queue.Empty:
                    pass
                
                # 更新UI
                try:
                    self.root.update()
                except tk.TclError:
                    break
                    
        except Exception as e:
            print(f"❌ 窗口运行出错: {e}")
        finally:
            self.cleanup()
            
    def update_text(self, text):
        """更新显示文字"""
        if self.display_text and self.running:
            self.display_text.config(text=str(text))
            # print(f"📝 文字已更新: {text}")
            
    def cleanup(self):
        """清理资源"""
        self.running = False
        try:
            if self.root:
                self.root.destroy()
        except:
            pass
        # print("👋 浮窗已关闭")

# 全局变量和函数
_app_instance = None
_app_thread = None

def start_floating_window():
    """启动浮窗线程"""
    global _app_instance, _app_thread
    
    if _app_instance and _app_instance.running:
        return _app_instance
    
    # 创建新的应用实例
    _app_instance = FloatingTextApp()
    
    # 启动线程
    _app_thread = threading.Thread(target=_app_instance.run, daemon=True)
    _app_thread.start()
    
    # 给窗口一点启动时间
    time.sleep(0.5)
    
    return _app_instance

def setText(text):
    """外部调用函数 - 设置文字"""
    global _app_instance
    
    if _app_instance and _app_instance.running:
        _app_instance.message_queue.put(str(text))
        return True
    else:
        return False

def stop_floating_window():
    """停止浮窗"""
    global _app_instance
    if _app_instance:
        _app_instance.message_queue.put("STOP")

# 使用示例
if __name__ == "__main__":
    print("🎉 开始演示浮窗功能！")
    
    # 1. 启动浮窗
    app = start_floating_window()
    
    # 2. 演示不同文字更新
    messages = [
        "你好呀！你好呀！你好呀！你好呀！你好呀！你好呀！你好呀！你好呀！",
        "我在右下角陪你哦~",
        "随时可以更新我！",
        "Python真好玩！",
        "当前时间: " + time.strftime("%H:%M:%S")
    ]
    
    for msg in messages:
        setText(msg)
        time.sleep(2)
    
    # 3. 最后留个温馨的提示
    setText("浮窗演示结束，右键点击可关闭")
    
    # 保持主线程运行
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        stop_floating_window()
        print("再见啦！")