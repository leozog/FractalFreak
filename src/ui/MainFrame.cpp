#include "ui/MainFrame.h"


MainFrame::MainFrame(wxWindow* parent, AppData& dataRef) : MyFrame1(parent), data(dataRef)
{
	_fractalControls.push_back(ControlSet(bTransformHolder));
	_currentFractal = 0;
	m_textCtrl7->SetValue("Fraktal " + std::to_string(_currentFractal));
	m_frames->SetValue(std::to_string(_fractalControls[_currentFractal]._framesToNext));
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
		m_frames->SetValue(std::to_string(_fractalControls[_currentFractal]._framesToNext));
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
	m_frames->SetValue(std::to_string(_fractalControls[_currentFractal]._framesToNext));
	m_textCtrl7->SetValue("Fraktal " + std::to_string(_currentFractal));
	event.Skip();
}

void MainFrame::on_dimension_pick(wxCommandEvent& event)
{
	_fractalControls[_currentFractal].updateDimensions(m_choice1->GetSelection() + 2);
}

void MainFrame::onAnimateButton(wxCommandEvent& event)
{

	std::cout << data.animation->n_frames_ready();
	for (int i = 0; i < data.animation->n_frames(); i++)
	{
		drawFrame(data.animation->get_frame_x(i));
	}


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

void MainFrame::onGenerateButton(wxCommandEvent& event) {

	/*
		Czêœæ ³aduj¹ca fraktal do AppData
	*/

	data.animation->clear();

	for (int i = 0; i < _fractalControls.size(); i++)
	{

		std::vector<Transform_2D> transforms = _fractalControls[i].exportTransforms2D();
		data.animation->path->add(std::make_unique<simple_fractal::Parameters>(simple_fractal::Parameters(transforms)),2.0);
	}

	/*
		Od tego momentu to nie mój problem (do czasu wystawienia oceny) -- generowanie fraktali
	*/

	try
	{
		data.animation->render(60, -1, 640, 480); // fps, n_of_threads, W, H
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}


void MainFrame::drawFrame(std::shared_ptr<wxImage> img)
{
	// init
	wxClientDC dc1(m_fractalPanel);
	wxBufferedDC dc(&dc1);

	int width, height;
	m_fractalPanel->GetSize(&width, &height);

	dc.DestroyClippingRegion();
	dc.SetClippingRegion(0, 0, width, height);

	// draw white bg
	dc.SetBackground(*wxBLACK_BRUSH);
	dc.Clear();

	// draw frame
	dc.DrawBitmap(wxBitmap(*img), 0, 0);
}

void MainFrame::onFileLoad(wxCommandEvent& event)
{
	wxFileDialog
		openFileDialog(this, _("Otworz plik tekstowy z fraktalem"), "", "",
			"TXT z fraktalem (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;     // the user changed idea...

	std::ifstream input;
	input.open(openFileDialog.GetPath().ToStdString());

	std::string firstLine;
	getline(input, firstLine);

	std::stringstream processing(firstLine);

	std::string elem;
	getline(processing, elem, ',');

	m_widthtxt->SetValue(elem);

	getline(processing, elem, ',');
	m_heighttxt->SetValue(elem);

	getline(processing, elem, ',');
	// TODO

	getline(processing, elem, ',');
	int dimensions = std::atoi(elem.data());

	_fractalControls[_currentFractal].Hide();
	_fractalControls.clear();
	_currentFractal = 0;

	if (dimensions == 0)
	{

		getline(input, elem); // pomiñ pozycjê kamery
		getline(input, elem);
		int fractals = std::atoi(elem.data());
		for (int i = 0; i < fractals; i++)
		{
			getline(input, elem);
			int transforms = std::atoi(elem.data());
			_fractalControls.push_back(ControlSet(bTransformHolder, 2, true));
			for (int j = 0; j < transforms; j++)
			{
				_fractalControls[i].AddLine();

				getline(input, elem); // transformacja
				std::stringstream transform(elem);

				std::vector<std::string> inputs;
				for (int k = 0; k < 6; k++)
				{
					getline(transform, elem, ' ');
					inputs.push_back(elem);
				}

				_fractalControls[i].setLine(inputs, j);
				
				
				
			}

			if (i == 0)
			{
				_fractalControls[0].Show();
			}
			getline(input, elem);
			_fractalControls[i]._framesToNext = std::atoi(elem.data()); //frames
		}
	}

		

}