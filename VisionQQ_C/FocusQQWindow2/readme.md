## FocusQQWindow2
对窗口中含有`QQ`文字的窗口置顶并放在最左边

### 使用方法

```Python
import ctypes

def focus():
    dll=ctypes.CDLL(os.path.abspath('FocusQQWindow2.dll'))
    # extern "C" int __declspec(dllexport) focus()
    dll.focus()

focus()
```
