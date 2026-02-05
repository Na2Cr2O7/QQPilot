@REM 7z.exe x WinPython64-3.13.7.0dot.7z -oPython\
@REM arm版本时，先运行python安装程序
python-3.14.2-arm64.exe

PythonPath.cmd -m pip install -r requirements.txt -i https://pypi.tuna.tsinghua.edu.cn/simple/