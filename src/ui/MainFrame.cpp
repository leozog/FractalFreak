#include "ui/MainFrame.h"


MainFrame::MainFrame(wxWindow* parent, AppData& dataRef) : MyFrame1(parent), data(dataRef)
{
	_fractalControls.push_back(ControlSet(bTransformHolder));
	_currentFractal = 0;
}


void MainFrame::onTransformDelete(wxCommandEvent& event)
{
	_fractalControls[_currentFractal].HandleTransformDestroy(event.GetId());
	event.Skip();
}

void MainFrame::onTransformAdd(wxCommandEvent& event)
{
	_fractalControls[_currentFractal].AddLine();
	event.Skip();
	
}

void MainFrame::fractal_left_button(wxCommandEvent& event)
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

void MainFrame::fractal_right_button(wxCommandEvent& event)
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

void MainFrame::on_dimension_pick(wxCommandEvent& event)
{
	_fractalControls[_currentFractal].updateDimensions(m_choice1->GetSelection() + 2);
}

void MainFrame::onAnimateButton(wxCommandEvent& event)
{
	// init
	// frc_calc.calcSize(0);
	// frc_calc.calcSize(1);
	// frc_calc.calcChange();

	// drawing and calculating loop
	// for (int i = 0; i < frc_calc.get_MainFrames_amount() + 1; i++)
	// {
	//	frc_calc.createBitmap();
	//	drawMainFrame();
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

	// draw MainFrame
	dc.DrawBitmap(wxBitmap(frc_calc.MainFrame), 0, 0);
	*/
}