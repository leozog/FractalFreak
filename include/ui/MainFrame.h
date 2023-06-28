#pragma once

#include "BaseFrame.h"
#include "FractalControls.h"
#include <wx/image.h>
#include <wx/dc.h>
#include <wx/dcbuffer.h>
#include "AppData.h"
#include <wx/filedlg.h>
#include <fstream>
#include<sstream>

class MainFrame : public MyFrame1
{

protected:

	void fractal_left_button(wxCommandEvent& event) override;
	void fractal_right_button(wxCommandEvent& event) override;
	void on_dimension_pick(wxCommandEvent& event) override;
	void onAnimateButton(wxCommandEvent& event) override;
	void onGenerateButton(wxCommandEvent& event) override;
	void onFileLoad(wxCommandEvent& event) override;
	void onFramesText(wxCommandEvent& event) override;

	// displays wxImage frame
	void drawFrame(wxImage img);

	int _currentFractal;

	std::vector<ControlSet> _fractalControls;

	AppData& data;

public:

	MainFrame(wxWindow* parent, AppData & _dataRef);
	~MainFrame() {};

	void onTransformDelete(wxCommandEvent& event) override;
	void onTransformAdd(wxCommandEvent& event) override;
	void drawFrame(std::shared_ptr<wxImage> img);



	

};