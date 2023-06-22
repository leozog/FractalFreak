#pragma once

#include "projekt.h"
#include "FractalControls.h"

class Frame : public MyFrame1
{
private:

protected:

	void fractal_left_button(wxCommandEvent& event) override;
	void fractal_right_button(wxCommandEvent& event) override;
	void on_dimension_pick(wxCommandEvent& event) override;
	void onAnimateButton(wxCommandEvent& event) override;

	int _currentFractal;

	std::vector<ControlSet> _fractalControls;

public:

	Frame(wxWindow* parent);
	~Frame() {};

	void onTransformDelete(wxCommandEvent& event) override;
	void onTransformAdd(wxCommandEvent& event) override;

};