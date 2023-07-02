///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/gauge.h>
#include <wx/timer.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyWindow : public wxFrame
{
private:
protected:
	wxStaticText* m_staticText2;
	wxButton* m_fractal_left;
	wxTextCtrl* m_textCtrl7;
	wxButton* m_fractal_right;
	wxChoice* m_choice1;
	wxTextCtrl* m_frames;
	wxBoxSizer* bTransformHolder;
	wxStaticText* m_staticText1;
	wxButton* m_button2;
	wxStaticText* m_staticText3;
	wxButton* m_renderbutton;
	wxButton* m_button_beginAnimation;
	wxStaticText* m_staticText4;
	wxTextCtrl* m_widthtxt;
	wxTextCtrl* m_heighttxt;
	wxStaticText* m_staticText5;
	wxTextCtrl* m_itertxt;
	wxTextCtrl* m_timetxt;
	wxStaticText* m_staticText6;
	wxTextCtrl* m_textCtrl_X;
	wxTextCtrl* m_textCtrl_Y;
	wxTextCtrl* m_textCtrl_Z;
	wxBoxSizer* b_cameraSizer;
	wxGauge* m_progress;
	wxBoxSizer* bPanelSizer;
	wxPanel* m_fractalPanel;
	wxMenuBar* m_menubar1;
	wxMenu* m_filemenu;
	wxTimer* _timer;

	// Virtual event handlers, override them in your derived class
	virtual void onCloseEvent(wxCloseEvent& event) { event.Skip(); }
	virtual void fractal_left_button(wxCommandEvent& event) { event.Skip(); }
	virtual void fractal_right_button(wxCommandEvent& event) { event.Skip(); }
	virtual void on_dimension_pick(wxCommandEvent& event) { event.Skip(); }
	virtual void onFramesText(wxCommandEvent& event) { event.Skip(); }
	virtual void onTransformAdd(wxCommandEvent& event) { event.Skip(); }
	virtual void onGenerateButton(wxCommandEvent& event) { event.Skip(); }
	virtual void onAnimateButton(wxCommandEvent& event) { event.Skip(); }
	virtual void onWidthText(wxCommandEvent& event) { event.Skip(); }
	virtual void onHeightText(wxCommandEvent& event) { event.Skip(); }
	virtual void onIterText(wxCommandEvent& event) { event.Skip(); }
	virtual void onFileLoad(wxCommandEvent& event) { event.Skip(); }
	virtual void onSaveAs(wxCommandEvent& event) { event.Skip(); }
	virtual void onTimer(wxCommandEvent& event) { event.Skip(); }
	virtual void onExport(wxCommandEvent& event) { event.Skip(); }

public:
	MyWindow(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString &title = wxEmptyString, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxSize(1000, 500), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~MyWindow();

	virtual void onTransformDelete(wxCommandEvent &event) { event.Skip(); }
};
