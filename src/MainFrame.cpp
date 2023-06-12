#include "MainFrame.h"


void MainFrame::playAnimation(wxCommandEvent& event)
{
	// init
	frc_calc.calcSize(0);
	frc_calc.calcSize(1);
	frc_calc.calcChange();

	// drawing and calculating loop
	for (int i = 0; i < frc_calc.get_frames_amount() + 1; i++)
	{
		frc_calc.createBitmap();
		drawFrame();
		frc_calc.updateTransformations();
	}
}

void MainFrame::drawFrame()
{
	// init
	wxClientDC dc1(drawPanel);
	wxBufferedDC dc(&dc1);

	int width, height;
	drawPanel->GetSize(&width, &height);

	dc.DestroyClippingRegion();
	dc.SetClippingRegion(0, 0, width, height);

	// draw white bg
	dc.SetBackground(*wxWHITE_BRUSH);
	dc.Clear();

	// draw frame
	dc.DrawBitmap(wxBitmap(frc_calc.frame), 0, 0);
}

