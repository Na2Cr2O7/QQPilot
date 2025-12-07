// wxWidgets "Hello World" Program

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <iostream>
#include<Windows.h>
#include <shellscalingapi.h>
#include <chrono>  
#include <thread>
#include<cmath>
#include<memory>
#pragma comment(lib, "Shcore.lib") 
#include <combaseapi.h>
#include <cstdlib>

#include"MyProjectBase.h"

bool DPIAwarenessPrologue()
{
	// 尝试 Windows 8.1+ 方法
	HMODULE shcore = LoadLibraryW(L"shcore.dll");
	if (shcore) {
		typedef HRESULT(WINAPI* SetProcessDpiAwarenessFunc)(PROCESS_DPI_AWARENESS);
		auto func = (SetProcessDpiAwarenessFunc)GetProcAddress(shcore, "SetProcessDpiAwareness");
		if (func) {
			HRESULT hr = func(PROCESS_SYSTEM_DPI_AWARE);
			FreeLibrary(shcore);
			return SUCCEEDED(hr);
		}
		FreeLibrary(shcore);
	}

	// 回退到 Vista~Win8 方法（仅系统 DPI 感知）
	typedef BOOL(WINAPI* SetProcessDPIAwareFunc)();
	HMODULE user32 = GetModuleHandleW(L"user32.dll");
	if (user32) {
		auto func = (SetProcessDPIAwareFunc)GetProcAddress(user32, "SetProcessDPIAware");
		if (func) {
			return func() != FALSE;
		}
	}

	return false; // 不支持
}
class Mainwin :public MyFrame1
{
public:
	Mainwin(wxWindow* parent = nullptr) :MyFrame1(parent) {}
	void Install_Click(wxCommandEvent& event);
};
class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};
bool MyApp::OnInit()
{
	DPIAwarenessPrologue();
	Mainwin* mainwin = new Mainwin();
	mainwin->Show(true);
	return true;

}
void Mainwin::Install_Click(wxCommandEvent& event)
{
	/*	   install.exe
	system("7z.exe x WinPython64-3.13.7.0dot.7z -oPython\\");
	system("PythonPath.cmd -m pip install -r requirements.txt -i https://pypi.tuna.tsinghua.edu.cn/simple/");
	system("下载助手.bat");
	*/
	LPCWSTR lpApplicationName = L"install.exe";
	LPWSTR lpCommandLine = const_cast<LPWSTR>(L"");
	STARTUPINFOW si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	BOOL ret = CreateProcess(lpApplicationName,
		lpCommandLine,
		NULL,
		NULL,
		FALSE,
		CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&si,
		&pi);
	if (not ret)
	{
		MessageBox(NULL, L"无法安装", L"错误", MB_OK | MB_ICONEXCLAMATION);
		return;
	}else
	{
		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		MessageBox(NULL, L"安装成功", L"完成", MB_OK | MB_ICONINFORMATION);

	}
}
wxIMPLEMENT_APP(MyApp);