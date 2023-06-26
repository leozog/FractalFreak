///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ui/GUI.h"

///////////////////////////////////////////////////////////////////////////

GUIMainFrame::GUIMainFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer *mainSizer;
	mainSizer = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer *settingsSizer;
	settingsSizer = new wxBoxSizer(wxVERTICAL);

	renderAnimationButton = new wxButton(this, wxID_ANY, wxT("render animation"), wxDefaultPosition, wxDefaultSize, 0);
	settingsSizer->Add(renderAnimationButton, 0, wxALL, 5);

	playAnimationButton = new wxButton(this, wxID_ANY, wxT("play animation"), wxDefaultPosition, wxDefaultSize, 0);
	settingsSizer->Add(playAnimationButton, 0, wxALL, 5);

	mainSizer->Add(settingsSizer, 0, wxEXPAND, 5);

	drawPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	drawPanel->SetBackgroundColour(wxColour(255, 255, 255));

	mainSizer->Add(drawPanel, 1, wxEXPAND | wxALL, 5);

	this->SetSizer(mainSizer);
	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	renderAnimationButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GUIMainFrame::renderAnimation), NULL, this);
	playAnimationButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GUIMainFrame::playAnimation), NULL, this);
}

GUIMainFrame::~GUIMainFrame()
{
	// Disconnect Events
	renderAnimationButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GUIMainFrame::renderAnimation), NULL, this);
	playAnimationButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GUIMainFrame::playAnimation), NULL, this);
}
