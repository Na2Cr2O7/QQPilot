// wxWidgets "Hello World" Program

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/filedlg.h>
#include <wx/file.h>
#include <wx/dir.h>
#include <wx/filename.h>

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
#include "inicontrol.h"
#include <string>
#include "inicpp.hpp"
#include<fstream>
using namespace inicpp;
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
	
	Mainwin(wxWindow* parent = nullptr) :MyFrame1(parent)
	{
		IniManager* ini = nullptr;
		try
		{

		ini =new IniManager("config.ini");
		
		version = static_cast<wxString>((*ini)["general"]["version"].get<std::string>());
		}
		catch(std::exception e)
		{
			wxMessageBox(e.what());
		}
		if (ini)
		{
			delete ini;
		}
		this->m_vision->SetLabel(version);

		wxDir dir(wxGetCwd());
		wxString filename;
		bool cont = dir.GetFirst(&filename);
		//wxString fnBuffer="新版本文件:\n\n";

		this->m_richText1->SetValue("新版本文件:\n\n\n\n");
		wxString fnBuffer;
		listEveryFile(wxGetCwd(),&fnBuffer);
		this->m_richText1->SetValue(fnBuffer);

		//while (cont)
		//{
			//this->m_richText1->SetValue(this->m_richText1->GetValue()+filename);

			//fnBuffer += filename;
			//fnBuffer += "\n\n";
			//cont = dir.GetNext(&filename);
		//}
		//this->m_richText1->SetValue(fnBuffer);

	}
	void listEveryFile(const wxString path, wxString* result);

	virtual void m_SelectPath_Click(wxCommandEvent& event);
	virtual void m_transfer_Click(wxCommandEvent& event);
private:
	wxString version;
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
void Mainwin::m_SelectPath_Click(wxCommandEvent& event)
{
	wxString defaultPath = wxT("/");
	wxDirDialog dialog(nullptr,
		wxT("选择旧版本目录"),
		defaultPath, wxDD_NEW_DIR_BUTTON);
	if (dialog.ShowModal() == wxID_OK)
	{
		wxString path = dialog.GetPath();
		wxMessageBox(path);
		this->m_pathInput->SetValue(path);
		this->m_richText1->SetValue(this->m_richText1->GetValue() + "\n\n旧版本文件:\n\n\n\n");
		wxString fnBuffer;
		this->listEveryFile(path, &fnBuffer);
		this->m_richText1->SetValue(this->m_richText1->GetValue()+fnBuffer);

	}
}
void Mainwin::listEveryFile(const wxString path,wxString* result)
{
	wxDir dir(path);
	wxString fnBuffer;
	wxString filename;
	bool cont = dir.GetFirst(&filename);


	while (cont)
	{
		//this->m_richText1->SetValue(this->m_richText1->GetValue()+filename);

		fnBuffer += filename;
		fnBuffer += "\n\n";
		cont = dir.GetNext(&filename);
	}
	(*result)=fnBuffer;
	//this->m_richText1->SetValue(this->m_richText1->GetValue() + fnBuffer);
}
static void listEveryFileAsVector(const wxString& directory , std::vector<wxString>* files)
{
	wxDir dir(directory);
	wxString filename;
	bool cont = dir.GetFirst(&filename);
	 

	while (cont)
	{
		files->emplace_back(filename);
		cont = dir.GetNext(&filename);
	}

}
void Mainwin::m_transfer_Click(wxCommandEvent& event)
{
	const std::string general = "general";
	wxString oldPath = this->m_pathInput->GetValue();
	if (not wxDirExists(oldPath))
	{
		wxMessageBox(wxT("目录不存在"),wxT("错误"), wxICON_INFORMATION);
		return;
	}
	{
		IniManager ini("config.ini");
		if (wxFileExists(oldPath + "\\config.ini"))
		{

			IniManager ini2((oldPath + "\\config.ini").ToStdString());

			for (auto& kv : ini2.sectionMap(general))
			{
				ini.set(general, kv.first, kv.second);

			}
			ini.set(general, "version", version.ToStdString());

			//ini["general"]=ini2["general"];
		}
		else
		{
			wxMessageBox(wxT("没有找到旧版本配置文件"), wxT("注意"), wxICON_INFORMATION);
			//IniManager ini2("config.ini");
			//for (auto& kv : ini2.sectionMap(general))
			//{
			//	ini -> set(general, kv.first, kv.second);

			//}

		}
	}


	std::vector<wxString> oldFiles;
	std::vector<wxString> newFiles;
	listEveryFileAsVector(wxGetCwd(), &newFiles);
	listEveryFileAsVector(oldPath, &oldFiles);
	for (auto& w : oldFiles)
	{
		bool ok=wxRemoveFile(oldPath+"\\"+w);
		this->m_richText1->SetValue(this->m_richText1->GetValue()+w + (ok ? "删除成功\n\n" : "删除失败\n\n"));


	}
	for (const wxString& fn : newFiles)
	{

		wxFileName srcFile(fn);
		if (!srcFile.IsOk() || !srcFile.FileExists())
		{
			continue;
		}

		wxFileName destFile(oldPath, srcFile.GetFullName());
		if (!destFile.IsDirWritable())
		{
			this->m_richText1->SetValue(this->m_richText1->GetValue() + fn+"不可写入\n\n");

			continue;
		}
		//wxMessageBox(srcFile.GetAbsolutePath(), destFile.GetFullPath());

		if (!wxCopyFile(fn, destFile.GetFullPath(), true))
		{
			//!wxRenameFile(fn, destFile.GetFullPath(), true)
			this->m_richText1->SetValue(this->m_richText1->GetValue() + fn + "移动失败\n\n");
			continue;
		}
		this->m_richText1->SetValue(this->m_richText1->GetValue() + fn + "移动成功\n\n");
	}
	std::ofstream ofs((oldPath + "\\update.cmd").ToStdString());
	ofs << "PythonPath.cmd -m pip install -r requirements.txt";
	ofs.close();
	wxMessageBox("你可能需要运行update.cmd更新python库","迁移成功", wxYES_DEFAULT | wxICON_QUESTION);



	//wxFileName fname(wxT("MyFile.txt"));
	//wxMessageBox();


}
wxIMPLEMENT_APP(MyApp);