#include "../include/Frame.h"


Frame::Frame(wxWindow* parent) : MyFrame1(parent)
{
	_fractalControls.push_back(ControlSet(bTransformHolder));
	_currentFractal = 0;
}


void Frame::onTransformDelete(wxCommandEvent& event)
{
	_fractalControls[_currentFractal].HandleTransformDestroy(event.GetId());
	event.Skip();
}

void Frame::onTransformAdd(wxCommandEvent& event)
{
	_fractalControls[_currentFractal].AddLine();
	event.Skip();
	
}

void Frame::fractal_left_button(wxCommandEvent& event)
{
	if (_currentFractal > 0)
	{
		_fractalControls[_currentFractal].Hide();
		_currentFractal--;
		_fractalControls[_currentFractal].Show();
		m_textCtrl7->SetValue("Fraktal " + std::to_string(_currentFractal));
	}
	event.Skip();
}

void Frame::fractal_right_button(wxCommandEvent& event)
{
	_fractalControls[_currentFractal].Hide();

	if ((_currentFractal + 1) == _fractalControls.size())
	{
		_fractalControls.push_back(ControlSet(bTransformHolder));
		_currentFractal++;
	}
	else
	{
		_currentFractal++;
		_fractalControls[_currentFractal].Show();
	}
	m_textCtrl7->SetValue("Fraktal " + std::to_string(_currentFractal));
	event.Skip();
}

void Frame::on_dimension_pick(wxCommandEvent& event)
{
	_fractalControls[_currentFractal].updateDimensions(m_choice1->GetSelection() + 2);
}

void Frame::onAnimateButton(wxCommandEvent& event)
{
	// init
	// frc_calc.calcSize(0);
	// frc_calc.calcSize(1);
	// frc_calc.calcChange();

	// drawing and calculating loop
	// for (int i = 0; i < frc_calc.get_frames_amount() + 1; i++)
	// {
	//	frc_calc.createBitmap();
	//	drawFrame();
	//	frc_calc.updateTransformations();
	// }

	/*
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
	*/
}