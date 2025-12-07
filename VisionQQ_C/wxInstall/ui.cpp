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
	this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer(wxVERTICAL);

	m_panel5 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	bSizer6->Add(m_panel5, 1, wxEXPAND | wxALL, 5);

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer(wxHORIZONTAL);


	bSizer5->Add(0, 0, 1, wxEXPAND, 5);

	m_staticText2 = new wxStaticText(this, wxID_ANY, _("即将开始安装VisionQQ"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText2->Wrap(-1);
	bSizer5->Add(m_staticText2, 0, wxALL, 5);


	bSizer5->Add(0, 0, 1, wxEXPAND, 5);


	bSizer6->Add(bSizer5, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer(wxHORIZONTAL);


	bSizer4->Add(0, 0, 1, wxEXPAND, 5);

	m_button3 = new wxButton(this, wxID_ANY, _("安装"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(m_button3, 0, wxALL, 5);


	bSizer4->Add(0, 0, 1, wxEXPAND, 5);


	bSizer6->Add(bSizer4, 1, wxEXPAND, 5);

	m_staticText3 = new wxStaticText(this, wxID_ANY, _("基于窗口自动化的 QQ 自动回复机器人"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText3->Wrap(-1);
	bSizer6->Add(m_staticText3, 0, wxALL, 5);


	this->SetSizer(bSizer6);
	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	m_button3->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::Install_Click), NULL, this);
}

MyFrame1::~MyFrame1()
{
}
