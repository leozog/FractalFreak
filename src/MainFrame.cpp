#include "MainFrame.h"

void MainFrame::renderAnimation(wxCommandEvent &event)
{
	data.animation.render();
	// TODO: podglad animacji podczas renderowania
}

void MainFrame::playAnimation(wxCommandEvent &event)
{
	// drawing loop
	for (int i = 0; i < data.animation.n_frames(); i++)
	{
		drawFrame(data.animation.get_frame_x(i));
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
