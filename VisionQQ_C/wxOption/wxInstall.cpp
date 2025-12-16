// wxWidgets "Hello World" Program

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/config.h>
#include <wx/fileconf.h>
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
#include <charconv>
//#define _ENBABLE_INICPP_STD_WSTRING_
#include "inicpp.hpp"
#include <vector>
#include <wx/file.h>
#include <wx/dir.h>
using namespace inicpp;

#include"MyProjectBase.h"

static void listEveryFileAsVector(const wxString& directory, std::vector<std::string>* files)
{
	wxDir dir(directory);
	wxString filename;
	bool cont = dir.GetFirst(&filename);


	while (cont)
	{
		files->emplace_back(filename.ToStdString());
		cont = dir.GetNext(&filename);
	}

}

static bool isnumeric(const std::string& s)
{
	if (s.empty()) return false;
	float f;
	auto result = std::from_chars(s.data(), s.data() + s.size(), f);
	return result.ec == std::errc{} && result.ptr == s.data() + s.size();
}
static bool isnumeric(const wxString& s)
{
	const std::string w = s.ToStdString();
	return isnumeric(w);
}
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
const std::string general = "general";
static wxString iniget(IniManager* ini, const std::string key)
{
	return static_cast<wxString>((*ini)[general][key].get<std::string>());
}
static void iniwrite(IniManager* ini, const std::string& key, const std::string& value)
{
	(*ini)[general][key] = value;
}
static std::string inigetStdString(IniManager* ini, const std::string key)
{
	auto w = (*ini)[general][key];
	w._value;
	return (*ini)[general][key];
}
void setTextBox(wxTextCtrl* textBox, const wxString& text)
{
	textBox->SetValue(text);
}
static std::string getTextBox(const wxTextCtrl* textBox)
{
	return textBox->GetValue().ToStdString();
}
static std::string getCheckBox(const wxCheckBox* checkBox)
{
	return checkBox->GetValue() ? "True":"False";
}
static void setCheckBox(wxCheckBox* checkBox, const wxString& text)
{
	checkBox->SetValue(text == "True");

}
class Mainwin :public MyFrame1
{
public:
	IniManager* ini = nullptr;
	Mainwin(wxWindow* parent = nullptr) :MyFrame1(parent)
	{

		ini = new IniManager("config.ini");
		//IniParser ini2(L"config.ini");
		wxFileConfig* config= new wxFileConfig(wxEmptyString, wxEmptyString, wxT("config.ini"));
		//config->SetPath("/general");
		this->m_version->SetLabel(iniget(ini, "version"));
		setTextBox(m_windowWidth, iniget(ini, "width"));
		setTextBox(m_windowHeight, iniget(ini, "height"));
		setTextBox(m_windowHeight, iniget(ini, "height"));
		setTextBox(m_modelName, iniget(ini, "modelname"));
		setCheckBox(m_visionmodel, iniget(ini, "isVisionModel"));
		setTextBox(m_imageCount, iniget(ini, "maxImageCount"));
		setTextBox(m_apiKey, iniget(ini, "api_key"));
		wxString url = iniget(ini, "server_url");
		setTextBox(m_server, url);
		m_useBuiltin->SetValue(url == "builtin");
		m_useOllama->SetValue(url == "ollama");
		setTextBox(m_scroll, iniget(ini, "scroll"));
		setCheckBox(m_ContainsImage, iniget(ini, "withImage"));
		m_ImagePossibly->SetValue((*ini)[general]["sendImagePossibility"].get<int>());
		setCheckBox(m_autoLogin, iniget(ini, "autoLogin"));
		setCheckBox(m_autoFocusing, iniget(ini, "autoFocusing"));
		setCheckBox(m_at, iniget(ini, "ATDetect"));
		wchar_t path[MAX_PATH];
		GetCurrentDirectory(MAX_PATH,path);
		std::wcscat(path, TEXT("\\config.ini"));
		path;
		size_t length = GetPrivateProfileString(TEXT("general"),TEXT("system"),TEXT("NONE"),nullptr,0,path);
		/*std::unique_ptr<wchar_t> text = std::make_unique<wchar_t>(length);*/
		std::unique_ptr<wchar_t[]> buffer = std::make_unique<wchar_t[]>(length + 1);
		//wchar_t* text = new wchar_t[length];
		GetPrivateProfileString(TEXT("general"), TEXT("system"), TEXT("NONE"), buffer.get(), length, path);
		std::wstring textstd(buffer.get());

		m_system->SetValue(textstd);
		buffer.reset();
		//wxMessageBox(ini2.getString(L"general", L"system"));

		delete ini;
	}
	virtual void m_windowWidth_TextChanged(wxCommandEvent& event)
	{
		if (not isnumeric(m_windowWidth->GetValue()))
		{
			m_windowWidth->SetValue("1280");
		}

	}
	virtual void m_windowHeight_TextChanged(wxCommandEvent& event)
	{
		if (not isnumeric(m_windowHeight->GetValue()))
		{
			m_windowHeight->SetValue("720");
		}
	}
	virtual void m_cleanImageCache_Click(wxCommandEvent& event) 
	{ 
		std::vector<std::string> files;
			listEveryFileAsVector(wxGetCwd(), &files);
			for (const std::string& i : files)
			{
				if ((i.find(".bmp") != std::string::npos) or (i.find(".png") != std::string::npos) or (i.find(".jpg") != std::string::npos))
				{
					wxRemoveFile(i);
				}
			}
			wxMessageBox("清理完成");

	}
	virtual void m_imageCount_TextChanged(wxCommandEvent& event)
	{
		if (not isnumeric(m_imageCount->GetValue()))
		{
			m_imageCount->SetValue("1");
		}
	}
	virtual void m_scroll_TextChanged(wxCommandEvent& event)
	{
		if (not isnumeric(m_scroll->GetValue()))
		{
			m_scroll->SetValue("4");
		}
	}
	virtual void m_quit(wxCommandEvent& event)
	{
		this->apply(event);
		this->cancel(event);
	}
	virtual void apply(wxCommandEvent& event) {
		IniManager* ini = new IniManager("config.ini");
		iniwrite(ini, "width", getTextBox(m_windowWidth));
		iniwrite(ini, "height", getTextBox(m_windowHeight));
		iniwrite(ini, "modelname", getTextBox(m_modelName));
		iniwrite(ini, "isVisionModel", getCheckBox(m_visionmodel)); // 假设有类似的 getCheckboxValue 函数
		iniwrite(ini, "maxImageCount", getTextBox(m_imageCount));
		iniwrite(ini, "api_key", getTextBox(m_apiKey));
		iniwrite(ini, "scroll", getTextBox(m_scroll));
		iniwrite(ini, "server_url", getTextBox(m_server));
		iniwrite(ini, "withImage", getCheckBox(m_ContainsImage)); // 假设有类似的 getCheckboxValue 函数
		iniwrite(ini, "sendImagePossibility", std::to_string(m_ImagePossibly->GetValue()));
		iniwrite(ini, "autoLogin", getCheckBox(m_autoLogin)); // 假设有类似的 getCheckboxValue 函数
		iniwrite(ini, "autoFocusing", getCheckBox(m_autoFocusing)); // 同上
		iniwrite(ini, "ATDetect", getCheckBox(m_at));
		iniwrite(ini, "width", getTextBox(m_windowWidth));
		iniwrite(ini, "height", getTextBox(m_windowHeight));
		iniwrite(ini, "modelname", getTextBox(m_modelName));


		delete ini;
	}
	virtual void cancel(wxCommandEvent& event)
	{
		wxExit();
	}
	virtual void m_useOllama_Clicked(wxCommandEvent& event) { 
		if (m_useOllama->GetValue())
		{
			m_server->SetValue("Ollama");
			m_server->Enable(false);
			m_apiKey->Enable(false);
		}
		else
		{
			m_server->Enable();
			m_apiKey->Enable();
		}
	}
	virtual void m_useBuiltin_Clicked(wxCommandEvent& event) {
		if (m_useBuiltin->GetValue())
		{
			m_server->SetValue("builtin");
			m_server->Enable(false);
			m_apiKey->Enable(false);
		}
		else
		{
			m_server->Enable();
			m_apiKey->Enable();
		}
	}
	virtual void openConfig(wxCommandEvent& event) 
	{ 
		system("notepad.exe config.ini");
	
	}
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

wxIMPLEMENT_APP(MyApp);