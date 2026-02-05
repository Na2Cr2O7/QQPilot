#include <stdlib.h>

int main()
{
    //由Convert.py自动生成,不要修改
	system("@REM 7z.exe x WinPython64-3.13.7.0dot.7z -oPython\\");
	system("PythonPath.cmd -m pip install -r requirements.txt -i https://pypi.tuna.tsinghua.edu.cn/simple/");
	system("下载助手.bat");

    return 0;
}