#pragma once

#include "MyWindow.h"
#include "FractalControls.h"
#include <wx/image.h>
#include <wx/dc.h>
#include <wx/dcbuffer.h>
#include "AppData.h"
#include <wx/filedlg.h>
#include <fstream>
#include <sstream>
#include "ui/FramesDrawer.h"

class MainWindow : public MyWindow
{
private:
	AppData &data;
	int _currentFractal;
	std::vector<ControlSet> _fractalControls;

	FramesDrawer framesdrawer;
	int chosenDimension;

protected:
	void fractal_left_button(wxCommandEvent &event) override;
	void fractal_right_button(wxCommandEvent &event) override;
	void on_dimension_pick(wxCommandEvent &event) override;
	void onAnimateButton(wxCommandEvent &event) override;
	void onGenerateButton(wxCommandEvent &event) override;
	void onFileLoad(wxCommandEvent &event) override;
	void onFramesText(wxCommandEvent &event) override;

public:
	MainWindow(wxWindow *parent, AppData &_dataRef);
	~MainWindow()
	{

	};

	void onTransformDelete(wxCommandEvent &event) override;
	void onTransformAdd(wxCommandEvent &event) override;
};