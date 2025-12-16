///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "MyProjectBase.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	this->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
	this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxVERTICAL);

	m_panel1 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	bSizer2->Add(m_panel1, 1, wxEXPAND | wxALL, 5);

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer(wxHORIZONTAL);

	m_staticText1 = new wxStaticText(this, wxID_ANY, _("窗口宽度"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText1->Wrap(-1);
	bSizer3->Add(m_staticText1, 0, wxALL, 5);

	m_windowWidth = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	m_windowWidth->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
	m_windowWidth->SetMaxSize(wxSize(100, -1));

	bSizer3->Add(m_windowWidth, 0, wxALL, 5);

	m_staticText11 = new wxStaticText(this, wxID_ANY, _("高度"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText11->Wrap(-1);
	bSizer3->Add(m_staticText11, 0, wxALL, 5);

	m_windowHeight = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	m_windowHeight->SetMaxSize(wxSize(100, -1));

	bSizer3->Add(m_windowHeight, 0, wxALL, 5);


	bSizer2->Add(bSizer3, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer(wxHORIZONTAL);

	m_staticText5 = new wxStaticText(this, wxID_ANY, _("模型名称"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText5->Wrap(-1);
	bSizer4->Add(m_staticText5, 0, wxALL, 5);

	m_modelName = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	m_modelName->SetMinSize(wxSize(300, -1));

	bSizer4->Add(m_modelName, 0, wxALL, 5);


	bSizer2->Add(bSizer4, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer(wxHORIZONTAL);

	m_visionmodel = new wxCheckBox(this, wxID_ANY, _("视觉模型"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer5->Add(m_visionmodel, 0, wxALL, 5);

	m_cleanImageCache = new wxButton(this, wxID_ANY, _("清理图片缓存"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer5->Add(m_cleanImageCache, 0, wxALL, 5);


	bSizer2->Add(bSizer5, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer(wxHORIZONTAL);

	m_staticText6 = new wxStaticText(this, wxID_ANY, _("解析图片数"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText6->Wrap(-1);
	bSizer10->Add(m_staticText6, 0, wxALL, 5);

	m_imageCount = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	m_imageCount->SetMaxSize(wxSize(50, -1));

	bSizer10->Add(m_imageCount, 0, wxALL, 5);

	m_staticText7 = new wxStaticText(this, wxID_ANY, _("本地模型解析>1张图片时速度极慢"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText7->Wrap(-1);
	bSizer10->Add(m_staticText7, 0, wxALL, 5);


	bSizer2->Add(bSizer10, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer(wxHORIZONTAL);

	m_staticText8 = new wxStaticText(this, wxID_ANY, _("APIKey"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText8->Wrap(-1);
	bSizer11->Add(m_staticText8, 0, wxALL, 5);

	m_apiKey = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
	m_apiKey->SetMinSize(wxSize(350, -1));

	bSizer11->Add(m_apiKey, 0, wxALL, 5);


	bSizer2->Add(bSizer11, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer111;
	bSizer111 = new wxBoxSizer(wxHORIZONTAL);

	m_staticText81 = new wxStaticText(this, wxID_ANY, _("服务器"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText81->Wrap(-1);
	bSizer111->Add(m_staticText81, 0, wxALL, 5);

	m_server = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer111->Add(m_server, 0, wxALL, 5);


	bSizer2->Add(bSizer111, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer(wxHORIZONTAL);

	m_useOllama = new wxCheckBox(this, wxID_ANY, _("Ollama"), wxDefaultPosition, wxDefaultSize, 0);
	m_useOllama->SetValue(true);
	bSizer18->Add(m_useOllama, 0, wxALL, 5);

	m_useBuiltin = new wxCheckBox(this, wxID_ANY, _("内置模型"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer18->Add(m_useBuiltin, 0, wxALL, 5);


	bSizer2->Add(bSizer18, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer(wxHORIZONTAL);

	m_staticText12 = new wxStaticText(this, wxID_ANY, _("框选消息时长"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText12->Wrap(-1);
	bSizer19->Add(m_staticText12, 0, wxALL, 5);

	m_scroll = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	m_scroll->SetMaxSize(wxSize(50, -1));

	bSizer19->Add(m_scroll, 0, wxALL, 5);

	m_staticText13 = new wxStaticText(this, wxID_ANY, _("s"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText13->Wrap(-1);
	bSizer19->Add(m_staticText13, 0, wxALL, 5);


	bSizer2->Add(bSizer19, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer(wxHORIZONTAL);

	m_ContainsImage = new wxCheckBox(this, wxID_ANY, _("包含图片"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer21->Add(m_ContainsImage, 0, wxALL, 5);

	m_staticText15 = new wxStaticText(this, wxID_ANY, _("图片放置在在Images文件夹下"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText15->Wrap(-1);
	bSizer21->Add(m_staticText15, 0, wxALL, 5);


	bSizer2->Add(bSizer21, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer23;
	bSizer23 = new wxBoxSizer(wxHORIZONTAL);

	m_staticText16 = new wxStaticText(this, wxID_ANY, _("发送图片概率"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText16->Wrap(-1);
	bSizer23->Add(m_staticText16, 0, wxALL, 5);

	m_ImagePossibly = new wxSlider(this, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL);
	bSizer23->Add(m_ImagePossibly, 0, wxALL, 5);


	bSizer2->Add(bSizer23, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer(wxHORIZONTAL);

	m_autoLogin = new wxCheckBox(this, wxID_ANY, _("自动点击登录"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer24->Add(m_autoLogin, 0, wxALL, 5);

	m_autoFocusing = new wxCheckBox(this, wxID_ANY, _("持续将窗口置于最前"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer24->Add(m_autoFocusing, 0, wxALL, 5);


	bSizer2->Add(bSizer24, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer(wxHORIZONTAL);

	m_at = new wxCheckBox(this, wxID_ANY, _("只检查@"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer25->Add(m_at, 0, wxALL, 5);

	m_ok = new wxButton(this, wxID_ANY, _("确认"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer25->Add(m_ok, 0, wxALL, 5);

	m_apply = new wxButton(this, wxID_ANY, _("应用"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer25->Add(m_apply, 0, wxALL, 5);

	m_cancel = new wxButton(this, wxID_ANY, _("取消"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer25->Add(m_cancel, 0, wxALL, 5);


	bSizer2->Add(bSizer25, 1, wxEXPAND, 5);

	m_panel5 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	bSizer2->Add(m_panel5, 1, wxEXPAND | wxALL, 5);


	bSizer1->Add(bSizer2, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer26;
	bSizer26 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer27;
	bSizer27 = new wxBoxSizer(wxHORIZONTAL);

	m_staticText19 = new wxStaticText(this, wxID_ANY, _("提示文本请到config.ini中编辑"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText19->Wrap(-1);
	bSizer27->Add(m_staticText19, 0, wxALL, 5);


	bSizer27->Add(0, 0, 1, wxEXPAND, 5);

	m_version = new wxStaticText(this, wxID_ANY, _("V"), wxDefaultPosition, wxDefaultSize, 0);
	m_version->Wrap(-1);
	bSizer27->Add(m_version, 0, wxALL, 5);


	bSizer26->Add(bSizer27, 1, wxEXPAND, 5);

	m_button6 = new wxButton(this, wxID_ANY, _("打开config.ini"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer26->Add(m_button6, 0, wxALL, 5);

	m_system = new wxRichTextCtrl(this, wxID_ANY, _("w"), wxDefaultPosition, wxDefaultSize, 0 | wxVSCROLL | wxHSCROLL | wxNO_BORDER | wxWANTS_CHARS);
	m_system->Hide();
	m_system->SetMinSize(wxSize(-1, 8600));

	bSizer26->Add(m_system, 1, wxEXPAND | wxALL, 5);

	m_panel3 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	bSizer26->Add(m_panel3, 1, wxEXPAND | wxALL, 5);


	bSizer1->Add(bSizer26, 1, wxEXPAND, 5);


	this->SetSizer(bSizer1);
	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	m_windowWidth->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MyFrame1::m_windowWidth_TextChanged), NULL, this);
	m_windowHeight->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MyFrame1::m_windowHeight_TextChanged), NULL, this);
	m_cleanImageCache->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::m_cleanImageCache_Click), NULL, this);
	m_imageCount->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MyFrame1::m_imageCount_TextChanged), NULL, this);
	m_useOllama->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(MyFrame1::m_useOllama_Clicked), NULL, this);
	m_useBuiltin->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(MyFrame1::m_useBuiltin_Clicked), NULL, this);
	m_scroll->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MyFrame1::m_scroll_TextChanged), NULL, this);
	m_ok->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::m_quit), NULL, this);
	m_apply->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::apply), NULL, this);
	m_cancel->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::cancel), NULL, this);
	m_button6->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::openConfig), NULL, this);
}

MyFrame1::~MyFrame1()
{
}
