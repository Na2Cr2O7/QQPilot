import os
import importlib
import platform

if int(platform.version().split('.')[0])>=10:
    try:
        import win32more
        import optionWinUI3
    except:
        import Option4
        Option4.main()
else:
    import Option4
    Option4.main()
