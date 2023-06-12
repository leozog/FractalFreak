///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class GUIMainFrame
///////////////////////////////////////////////////////////////////////////////
class GUIMainFrame : public wxFrame
{
private:

protected:
	wxButton* playAnimationButton;
	wxPanel* drawPanel;

	// Virtual event handlers, override them in your derived class
	virtual void playAnimation(wxCommandEvent& event) { event.Skip(); }


public:

	GUIMainFrame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(1000, 700), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~GUIMainFrame();

};

