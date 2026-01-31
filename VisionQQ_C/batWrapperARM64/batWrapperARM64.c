#include <stdlib.h>
#define e(cmd)  system(cmd);
#define p(file)	system("PythonPath.cmd "file)  ;
#define cdexc(file) system("cd .\\data\\ && PythonPath.cmd "file);
int main()

{
#define 下载助手

	#ifdef install
	e("python-3.14.2-arm64.exe")
		e("PythonPath.cmd -m pip install -r requirements.txt -i https://pypi.tuna.tsinghua.edu.cn/simple/")
#endif // install
#ifdef  run
		e("ScaleToINI.exe")
		e("FocusqqWindow.exe")
		p("ScreenshotToUILayout.py")



#endif //  run
#ifdef 设置
		//e("cd .\\data\\ && PythonPath.cmd option5.py")
		cdexc("option5.py")
#endif // option
#ifdef 扩展管理器
		cdexc("extensionViewer.py")

#endif
#ifdef 下载助手
		cdexc(".\\download\\download.py");
#endif // download







}

