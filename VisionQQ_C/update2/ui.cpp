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

	m_simplebook1 = new wxSimplebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

	bSizer2->Add(m_simplebook1, 1, wxEXPAND | wxALL, 5);

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer(wxHORIZONTAL);


	bSizer5->Add(0, 0, 1, wxEXPAND, 5);

	m_staticText1 = new wxStaticText(this, wxID_ANY, _("配置迁移工具能够把旧版本的\nQQPilot或者VisionQQ升级到\n新版本并保留配置。"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText1->Wrap(-1);
	bSizer5->Add(m_staticText1, 0, wxALL, 5);


	bSizer5->Add(0, 0, 1, wxEXPAND, 5);


	bSizer2->Add(bSizer5, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer(wxHORIZONTAL);


	bSizer4->Add(0, 0, 1, wxEXPAND, 5);

	m_pathInput = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	m_pathInput->SetMinSize(wxSize(300, -1));

	bSizer4->Add(m_pathInput, 0, wxALL, 5);


	bSizer4->Add(0, 0, 1, wxEXPAND, 5);


	bSizer2->Add(bSizer4, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer(wxHORIZONTAL);


	bSizer41->Add(0, 0, 1, wxEXPAND, 5);

	m_SelectPath = new wxButton(this, wxID_ANY, _("选择旧版本data目录"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer41->Add(m_SelectPath, 0, wxALL, 5);


	bSizer41->Add(0, 0, 1, wxEXPAND, 5);


	bSizer2->Add(bSizer41, 1, wxEXPAND, 5);

	m_panel1 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	bSizer2->Add(m_panel1, 1, wxEXPAND | wxALL, 5);

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer(wxHORIZONTAL);

	m_vision = new wxStaticText(this, wxID_ANY, _("V"), wxDefaultPosition, wxDefaultSize, 0);
	m_vision->Wrap(-1);
	bSizer3->Add(m_vision, 0, wxALL, 5);


	bSizer3->Add(0, 0, 1, wxEXPAND, 5);

	m_transfer = new wxButton(this, wxID_ANY, _("迁移"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer3->Add(m_transfer, 0, wxALL, 5);


	bSizer3->Add(0, 0, 1, wxEXPAND, 5);


	bSizer2->Add(bSizer3, 1, wxEXPAND, 5);


	bSizer1->Add(bSizer2, 1, wxEXPAND, 5);

	m_richText1 = new wxRichTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 | wxVSCROLL | wxHSCROLL | wxNO_BORDER | wxWANTS_CHARS);
	bSizer1->Add(m_richText1, 1, wxEXPAND | wxALL, 5);


	this->SetSizer(bSizer1);
	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	m_SelectPath->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::m_SelectPath_Click), NULL, this);
	m_transfer->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::m_transfer_Click), NULL, this);
}

MyFrame1::~MyFrame1()
{
}
