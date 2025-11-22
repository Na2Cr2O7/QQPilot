
import ctypes
import os
def focus():
    dll=ctypes.CDLL(os.path.abspath('FocusQQWindow2.dll'))
    # extern "C" int __declspec(dllexport) focus()
    dll.focus()
while True:
    input("Press Enter to focus QQ window.")
    focus()
