#pragma once

#include "BaseFrame.h"
#include "FractalControls.h"
#include "AppData.h"

class MainFrame : public MyFrame1
{
private:

protected:

	void fractal_left_button(wxCommandEvent& event) override;
	void fractal_right_button(wxCommandEvent& event) override;
	void on_dimension_pick(wxCommandEvent& event) override;
	void onAnimateButton(wxCommandEvent& event) override;

	int _currentFractal;

	std::vector<ControlSet> _fractalControls;

	AppData& data;

public:

	MainFrame(wxWindow* parent, AppData & _dataRef);
	~MainFrame() {};

	void onTransformDelete(wxCommandEvent& event) override;
	void onTransformAdd(wxCommandEvent& event) override;

	

};