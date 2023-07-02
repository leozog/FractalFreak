#pragma once

#include <wx/dc.h>
#include <wx/dcbuffer.h>
#include <wx/image.h>
#include <wx/filedlg.h>

#include "MyWindow.h"
#include "FractalControls.h"

#include "AppData.h"
#include "ff/Animation.h"
#include "FractalsDefinitions.h"

#include "ui/FramesDrawer.h"

#include <fstream>
#include <sstream>
#include <functional>

enum AnimationState
{
	AWAITING,
	RENDERING,
	PLAYING
};

class MainWindow : public MyWindow
{
private:
	AppData &data;
	int _currentFractal;
	std::vector<ControlSet> _fractalControls;

	FramesDrawer framesdrawer;
	int chosenDimension;

	AnimationState _uiState;

protected:
	void fractal_left_button(wxCommandEvent &event) override;
	void fractal_right_button(wxCommandEvent &event) override;
	void on_dimension_pick(wxCommandEvent &event) override;
	void onAnimateButton(wxCommandEvent &event) override;
	void onGenerateButton(wxCommandEvent &event) override;
	void onFileLoad(wxCommandEvent &event) override;
	void onFramesText(wxCommandEvent &event) override;
	void onTimer(wxCommandEvent &event) override;
	void onSaveAs(wxCommandEvent &event) override;
	void onExport(wxCommandEvent& event) override;

	void setDimension(int newDimension, bool safe = true);
	void updateFractalUI();

public:
	MainWindow(wxWindow *parent, AppData &_dataRef);
	~MainWindow(){

	};

	void onTransformDelete(wxCommandEvent &event) override;
	void onTransformAdd(wxCommandEvent &event) override;
};