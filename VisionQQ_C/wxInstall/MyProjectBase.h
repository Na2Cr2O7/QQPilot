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
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame
{
private:

protected:
	wxPanel* m_panel5;
	wxStaticText* m_staticText2;
	wxButton* m_button3;
	wxStaticText* m_staticText3;

	// Virtual event handlers, override them in your derived class
	virtual void Install_Click(wxCommandEvent& event) { event.Skip(); }


public:

	MyFrame1(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("°²×°"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(536, 387), long style = wxCAPTION | wxCLOSE_BOX | wxDEFAULT_FRAME_STYLE | wxMINIMIZE | wxMINIMIZE_BOX | wxTAB_TRAVERSAL);

	~MyFrame1();

};

