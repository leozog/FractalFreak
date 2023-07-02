///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ui/MyWindow.h"

///////////////////////////////////////////////////////////////////////////

MyWindow::MyWindow(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer *bSizer1;
	bSizer1 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer *bSizer2;
	bSizer2 = new wxBoxSizer(wxVERTICAL);

	m_staticText2 = new wxStaticText(this, wxID_ANY, wxT("Fraktal"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText2->Wrap(-1);
	bSizer2->Add(m_staticText2, 0, wxALL, 5);

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer(wxHORIZONTAL);

	m_fractal_left = new wxButton(this, wxID_ANY, wxT("<"), wxDefaultPosition, wxSize(25, 25), 0);
	bSizer6->Add(m_fractal_left, 0, wxALL, 5);

	m_textCtrl7 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(-1, 25), wxTE_CENTER | wxTE_READONLY);
	bSizer6->Add(m_textCtrl7, 0, wxALL, 5);

	m_fractal_right = new wxButton(this, wxID_ANY, wxT(">"), wxDefaultPosition, wxSize(25, 25), 0);
	bSizer6->Add(m_fractal_right, 0, wxALL, 5);

	wxString m_choice1Choices[] = { wxT("2"), wxT("3") };
	int m_choice1NChoices = sizeof(m_choice1Choices) / sizeof(wxString);
	m_choice1 = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice1NChoices, m_choice1Choices, 0);
	m_choice1->SetSelection(0);
	bSizer6->Add(m_choice1, 0, wxALL, 5);

	m_frames = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	m_frames->SetToolTip(wxT("Liczba klatek w tym fraktalu"));

	bSizer6->Add(m_frames, 0, wxALL, 5);


	bSizer2->Add(bSizer6, 0, wxEXPAND, 5);

	bTransformHolder = new wxBoxSizer(wxVERTICAL);

	m_staticText1 = new wxStaticText(this, wxID_ANY, wxT("Przekształcenia"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText1->Wrap(-1);
	bTransformHolder->Add(m_staticText1, 0, wxALL, 5);

	wxBoxSizer* bTransformLine;
	bTransformLine = new wxBoxSizer(wxHORIZONTAL);


	bTransformHolder->Add(bTransformLine, 0, wxEXPAND, 5);

	m_button2 = new wxButton(this, wxID_ANY, wxT("+"), wxDefaultPosition, wxDefaultSize, 0);
	bTransformHolder->Add(m_button2, 0, wxALL, 5);


	bSizer2->Add(bTransformHolder, 1, wxEXPAND, 5);

	m_staticText3 = new wxStaticText(this, wxID_ANY, wxT("Ustawienia Animacji"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText3->Wrap(-1);
	bSizer2->Add(m_staticText3, 0, wxALL, 5);

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer(wxHORIZONTAL);

	m_renderbutton = new wxButton(this, wxID_ANY, wxT("Generuj"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer8->Add(m_renderbutton, 0, wxALL, 5);

	m_button_beginAnimation = new wxButton(this, wxID_ANY, wxT("Odtwórz"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer8->Add(m_button_beginAnimation, 0, wxALL, 5);


	bSizer7->Add(bSizer8, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer(wxHORIZONTAL);

	m_staticText4 = new wxStaticText(this, wxID_ANY, wxT("Rozmiar bitmap"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText4->Wrap(-1);
	bSizer9->Add(m_staticText4, 0, wxALL, 5);

	m_widthtxt = new wxTextCtrl(this, wxID_ANY, wxT("640"), wxDefaultPosition, wxDefaultSize, 0);
	m_widthtxt->SetToolTip(wxT("Szerokosc w pikselach"));

	bSizer9->Add(m_widthtxt, 0, wxALL, 5);

	m_heighttxt = new wxTextCtrl(this, wxID_ANY, wxT("480"), wxDefaultPosition, wxDefaultSize, 0);
	m_heighttxt->SetToolTip(wxT("Wysokosc w pikselach"));

	bSizer9->Add(m_heighttxt, 0, wxALL, 5);


	bSizer7->Add(bSizer9, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer(wxHORIZONTAL);

	m_staticText5 = new wxStaticText(this, wxID_ANY, wxT("Parametry renderu"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText5->Wrap(-1);
	bSizer10->Add(m_staticText5, 0, wxALL, 5);

	m_itertxt = new wxTextCtrl(this, wxID_ANY, wxT("20000"), wxDefaultPosition, wxDefaultSize, 0);
	m_itertxt->SetToolTip(wxT("Liczba iteracji"));

	bSizer10->Add(m_itertxt, 0, wxALL, 5);

	m_timetxt = new wxTextCtrl(this, wxID_ANY, wxT("20"), wxDefaultPosition, wxDefaultSize, 0);
	m_timetxt->SetToolTip(wxT("FPS animacji"));

	bSizer10->Add(m_timetxt, 0, wxALL, 5);


	bSizer7->Add(bSizer10, 0, wxEXPAND, 5);

	b_cameraSizer = new wxBoxSizer(wxHORIZONTAL);

	m_staticText6 = new wxStaticText(this, wxID_ANY, wxT("Kamera"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText6->Wrap(-1);
	b_cameraSizer->Add(m_staticText6, 0, wxALL, 5);

	m_textCtrl_X = new wxTextCtrl(this, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(50, -1), 0);
	m_textCtrl_X->SetToolTip(wxT("X"));

	b_cameraSizer->Add(m_textCtrl_X, 0, wxALL, 5);

	m_textCtrl_Y = new wxTextCtrl(this, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(50, -1), 0);
	b_cameraSizer->Add(m_textCtrl_Y, 0, wxALL, 5);

	m_textCtrl_Z = new wxTextCtrl(this, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(50, -1), 0);
	b_cameraSizer->Add(m_textCtrl_Z, 0, wxALL, 5);


	bSizer7->Add(b_cameraSizer, 0, wxEXPAND, 5);

	m_progress = new wxGauge(this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL);
	m_progress->SetValue(0);
	bSizer7->Add(m_progress, 0, wxALL | wxEXPAND, 5);


	bSizer2->Add(bSizer7, 1, wxEXPAND, 5);


	bSizer1->Add(bSizer2, 0, wxEXPAND, 5);

	bPanelSizer = new wxBoxSizer(wxVERTICAL);

	m_fractalPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(640, 480), wxTAB_TRAVERSAL);
	m_fractalPanel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));

	bPanelSizer->Add(m_fractalPanel, 1, wxEXPAND | wxALL, 5);


	bSizer1->Add(bPanelSizer, 1, wxEXPAND, 5);


	this->SetSizer(bSizer1);
	this->Layout();
	bSizer1->Fit(this);
	m_menubar1 = new wxMenuBar(0);
	m_filemenu = new wxMenu();
	wxMenuItem* m_menu_load;
	m_menu_load = new wxMenuItem(m_filemenu, wxID_ANY, wxString(wxT("Load...")), wxEmptyString, wxITEM_NORMAL);
	m_filemenu->Append(m_menu_load);

	wxMenuItem* m_menu_saveas;
	m_menu_saveas = new wxMenuItem(m_filemenu, wxID_ANY, wxString(wxT("Save As...")), wxEmptyString, wxITEM_NORMAL);
	m_filemenu->Append(m_menu_saveas);

	wxMenuItem* m_menu_export;
	m_menu_export = new wxMenuItem(m_filemenu, wxID_ANY, wxString(wxT("Export...")), wxEmptyString, wxITEM_NORMAL);
	m_filemenu->Append(m_menu_export);

	m_menubar1->Append(m_filemenu, wxT("File"));

	this->SetMenuBar(m_menubar1);


	this->Centre(wxBOTH);

	// Connect Events
	this->Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(MyWindow::onCloseEvent));
	m_fractal_left->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyWindow::fractal_left_button), NULL, this);
	m_fractal_right->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyWindow::fractal_right_button), NULL, this);
	m_choice1->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(MyWindow::on_dimension_pick), NULL, this);
	m_frames->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MyWindow::onFramesText), NULL, this);
	m_button2->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyWindow::onTransformAdd), NULL, this);
	m_renderbutton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyWindow::onGenerateButton), NULL, this);
	m_button_beginAnimation->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyWindow::onAnimateButton), NULL, this);
	m_widthtxt->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MyWindow::onWidthText), NULL, this);
	m_heighttxt->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MyWindow::onHeightText), NULL, this);
	m_itertxt->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MyWindow::onIterText), NULL, this);
	m_filemenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyWindow::onFileLoad), this, m_menu_load->GetId());
	m_filemenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyWindow::onSaveAs), this, m_menu_saveas->GetId());
	m_filemenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyWindow::onExport), this, m_menu_export->GetId());

	_timer = new wxTimer();
	_timer->Connect(wxEVT_TIMER, wxCommandEventHandler(MyWindow::onTimer), NULL, this);
}

MyWindow::~MyWindow()
{
	// Disconnect Events
	this->Disconnect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(MyWindow::onCloseEvent));
	m_fractal_left->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyWindow::fractal_left_button), NULL, this);
	m_fractal_right->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyWindow::fractal_right_button), NULL, this);
	m_choice1->Disconnect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(MyWindow::on_dimension_pick), NULL, this);
	m_frames->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MyWindow::onFramesText), NULL, this);
	m_button2->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyWindow::onTransformAdd), NULL, this);
	m_renderbutton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyWindow::onGenerateButton), NULL, this);
	m_button_beginAnimation->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyWindow::onAnimateButton), NULL, this);
	m_widthtxt->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MyWindow::onWidthText), NULL, this);
	m_heighttxt->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MyWindow::onHeightText), NULL, this);
	m_itertxt->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MyWindow::onIterText), NULL, this);
	_timer->Disconnect(wxEVT_TIMER, wxCommandEventHandler(MyWindow::onTimer), NULL, this);
}
