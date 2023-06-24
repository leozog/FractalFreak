///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/wx.h>
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class GUIMainFrame
///////////////////////////////////////////////////////////////////////////////
class GUIMainFrame : public wxFrame
{
private:
protected:
	wxButton *renderAnimationButton;
	wxButton *playAnimationButton;
	wxPanel *drawPanel;

	// Virtual event handlers, override them in your derived class
	virtual void renderAnimation(wxCommandEvent &event) { event.Skip(); }
	virtual void playAnimation(wxCommandEvent &event) { event.Skip(); }

public:
	GUIMainFrame(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString &title = wxEmptyString, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxSize(1000, 700), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~GUIMainFrame();
};
