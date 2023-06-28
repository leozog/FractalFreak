#include "ui/MainFrame.h"
/*
void MainFrame::renderAnimation(wxCommandEvent &event)
{
	try
	{
		data.animation->render(250, 8, 640, 480); // fps, n_of_threads, W, H
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
}

void MainFrame::playAnimation(wxCommandEvent &event)
{
	// drawing loop
	std::cout << data.animation->n_frames_ready();
	for (int i = 0; i < data.animation->n_frames(); i++)
	{
		drawFrame(data.animation->get_frame_x(i));
	}
}

void MainFrame::drawFrame(wxImage img)
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
	dc.DrawBitmap(wxBitmap(img), 0, 0);
}
*/