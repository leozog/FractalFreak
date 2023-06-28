///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ui/BaseFrame.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Fraktal"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer2->Add( m_staticText2, 0, wxALL, 5 );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );

	m_fractal_left = new wxButton( this, wxID_ANY, wxT("<"), wxDefaultPosition, wxSize( 25,25 ), 0 );
	bSizer6->Add( m_fractal_left, 0, wxALL, 5 );

	m_textCtrl7 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,25 ), wxTE_CENTER|wxTE_READONLY );
	bSizer6->Add( m_textCtrl7, 0, wxALL, 5 );

	m_fractal_right = new wxButton( this, wxID_ANY, wxT(">"), wxDefaultPosition, wxSize( 25,25 ), 0 );
	bSizer6->Add( m_fractal_right, 0, wxALL, 5 );

	wxString m_choice1Choices[] = { wxT("2"), wxT("3"), wxT("4") };
	int m_choice1NChoices = sizeof( m_choice1Choices ) / sizeof( wxString );
	m_choice1 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice1NChoices, m_choice1Choices, 0 );
	m_choice1->SetSelection( 0 );
	bSizer6->Add( m_choice1, 0, wxALL, 5 );

	m_frames = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_frames->SetToolTip( wxT("Liczba klatek w tym fraktalu") );

	bSizer6->Add( m_frames, 0, wxALL, 5 );


	bSizer2->Add( bSizer6, 0, wxEXPAND, 5 );

	bTransformHolder = new wxBoxSizer( wxVERTICAL );

	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Przekształcenia"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bTransformHolder->Add( m_staticText1, 0, wxALL, 5 );

	wxBoxSizer* bTransformLine;
	bTransformLine = new wxBoxSizer( wxHORIZONTAL );


	bTransformHolder->Add( bTransformLine, 0, wxEXPAND, 5 );

	m_button2 = new wxButton( this, wxID_ANY, wxT("+"), wxDefaultPosition, wxDefaultSize, 0 );
	bTransformHolder->Add( m_button2, 0, wxALL, 5 );


	bSizer2->Add( bTransformHolder, 1, wxEXPAND, 5 );

	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Ustawienia Animacji"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	bSizer2->Add( m_staticText3, 0, wxALL, 5 );

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );

	m_renderbutton = new wxButton( this, wxID_ANY, wxT("Generuj!"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( m_renderbutton, 0, wxALL, 5 );

	m_button_beginAnimation = new wxButton( this, wxID_ANY, wxT("Animuj!"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( m_button_beginAnimation, 0, wxALL, 5 );


	bSizer7->Add( bSizer8, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );

	m_widthtxt = new wxTextCtrl( this, wxID_ANY, wxT("640"), wxDefaultPosition, wxDefaultSize, 0 );
	m_widthtxt->SetToolTip( wxT("Szerokosc w pikselach") );

	bSizer9->Add( m_widthtxt, 0, wxALL, 5 );

	m_heighttxt = new wxTextCtrl( this, wxID_ANY, wxT("480"), wxDefaultPosition, wxDefaultSize, 0 );
	m_heighttxt->SetToolTip( wxT("Wysokosc w pikselach") );

	bSizer9->Add( m_heighttxt, 0, wxALL, 5 );


	bSizer7->Add( bSizer9, 0, wxEXPAND, 5 );


	bSizer2->Add( bSizer7, 1, wxEXPAND, 5 );


	bSizer1->Add( bSizer2, 0, wxEXPAND, 5 );

	m_fractalPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 640,480 ), wxTAB_TRAVERSAL );
	m_fractalPanel->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );

	bSizer1->Add( m_fractalPanel, 1, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );


	bSizer1->Add( bSizer3, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	m_menubar1 = new wxMenuBar( 0 );
	m_filemenu = new wxMenu();
	wxMenuItem* m_menu_load;
	m_menu_load = new wxMenuItem( m_filemenu, wxID_ANY, wxString( wxT("Load...") ) , wxEmptyString, wxITEM_NORMAL );
	m_filemenu->Append( m_menu_load );

	wxMenuItem* m_menu_save;
	m_menu_save = new wxMenuItem( m_filemenu, wxID_ANY, wxString( wxT("Save...") ) , wxEmptyString, wxITEM_NORMAL );
	m_filemenu->Append( m_menu_save );

	wxMenuItem* m_menu_saveas;
	m_menu_saveas = new wxMenuItem( m_filemenu, wxID_ANY, wxString( wxT("Save As...") ) , wxEmptyString, wxITEM_NORMAL );
	m_filemenu->Append( m_menu_saveas );

	m_menubar1->Append( m_filemenu, wxT("File") );

	this->SetMenuBar( m_menubar1 );


	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MyFrame1::onCloseEvent ) );
	m_fractal_left->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::fractal_left_button ), NULL, this );
	m_fractal_right->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::fractal_right_button ), NULL, this );
	m_choice1->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MyFrame1::on_dimension_pick ), NULL, this );
	m_frames->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MyFrame1::onFramesText ), NULL, this );
	m_button2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::onTransformAdd ), NULL, this );
	m_renderbutton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::onGenerateButton ), NULL, this );
	m_button_beginAnimation->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::onAnimateButton ), NULL, this );
	m_widthtxt->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MyFrame1::onWidthText ), NULL, this );
	m_heighttxt->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MyFrame1::onHeightText ), NULL, this );
}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MyFrame1::onCloseEvent ) );
	m_fractal_left->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::fractal_left_button ), NULL, this );
	m_fractal_right->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::fractal_right_button ), NULL, this );
	m_choice1->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MyFrame1::on_dimension_pick ), NULL, this );
	m_frames->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MyFrame1::onFramesText ), NULL, this );
	m_button2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::onTransformAdd ), NULL, this );
	m_renderbutton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::onGenerateButton ), NULL, this );
	m_button_beginAnimation->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::onAnimateButton ), NULL, this );
	m_widthtxt->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MyFrame1::onWidthText ), NULL, this );
	m_heighttxt->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MyFrame1::onHeightText ), NULL, this );

}
