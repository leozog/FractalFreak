#pragma once

#include "GUI.h"
#include "FractalCalculations.h"

// #include <wx/dcbuffer.h>
// #include <wx/colordlg.h>

// class implementing user interactions with the GUI
class MainFrame : public GUIMainFrame
{
protected:
	// plays the animation when playAnimationButton is clicked
	void playAnimation(wxCommandEvent &event) override;

	// displays wxImage frame
	void drawFrame();

	FractalCalculations frc_calc; // contains fractals and methods working on fractals

public:
	MainFrame(wxWindow *parent) : GUIMainFrame(parent) {}
};