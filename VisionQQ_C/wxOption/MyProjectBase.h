///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/slider.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame
{
private:

protected:
	wxPanel* m_panel1;
	wxStaticText* m_staticText1;
	wxTextCtrl* m_windowWidth;
	wxStaticText* m_staticText11;
	wxTextCtrl* m_windowHeight;
	wxStaticText* m_staticText5;
	wxTextCtrl* m_modelName;
	wxCheckBox* m_visionmodel;
	wxButton* m_cleanImageCache;
	wxStaticText* m_staticText6;
	wxTextCtrl* m_imageCount;
	wxStaticText* m_staticText7;
	wxStaticText* m_staticText8;
	wxTextCtrl* m_apiKey;
	wxStaticText* m_staticText81;
	wxTextCtrl* m_server;
	wxCheckBox* m_useOllama;
	wxCheckBox* m_useBuiltin;
	wxStaticText* m_staticText12;
	wxTextCtrl* m_scroll;
	wxStaticText* m_staticText13;
	wxCheckBox* m_ContainsImage;
	wxStaticText* m_staticText15;
	wxStaticText* m_staticText16;
	wxSlider* m_ImagePossibly;
	wxCheckBox* m_autoLogin;
	wxCheckBox* m_autoFocusing;
	wxCheckBox* m_at;
	wxButton* m_ok;
	wxButton* m_apply;
	wxButton* m_cancel;
	wxPanel* m_panel5;
	wxStaticText* m_staticText19;
	wxStaticText* m_version;
	wxButton* m_button6;
	wxRichTextCtrl* m_system;
	wxPanel* m_panel3;

	// Virtual event handlers, override them in your derived class
	virtual void m_windowWidth_TextChanged(wxCommandEvent& event) { event.Skip(); }
	virtual void m_windowHeight_TextChanged(wxCommandEvent& event) { event.Skip(); }
	virtual void m_cleanImageCache_Click(wxCommandEvent& event) { event.Skip(); }
	virtual void m_imageCount_TextChanged(wxCommandEvent& event) { event.Skip(); }
	virtual void m_useOllama_Clicked(wxCommandEvent& event) { event.Skip(); }
	virtual void m_useBuiltin_Clicked(wxCommandEvent& event) { event.Skip(); }
	virtual void m_scroll_TextChanged(wxCommandEvent& event) { event.Skip(); }
	virtual void m_quit(wxCommandEvent& event) { event.Skip(); }
	virtual void apply(wxCommandEvent& event) { event.Skip(); }
	virtual void cancel(wxCommandEvent& event) { event.Skip(); }
	virtual void openConfig(wxCommandEvent& event) { event.Skip(); }


public:

	MyFrame1(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("设置"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(1088, 688), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~MyFrame1();

};

