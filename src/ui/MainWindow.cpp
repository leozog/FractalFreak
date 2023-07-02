#include "ui/MainWindow.h"

MainWindow::MainWindow(wxWindow *parent, AppData &dataRef) : MyWindow(parent), data(dataRef), framesdrawer(data, m_fractalPanel)
{
	_fractalControls.push_back(ControlSet(bTransformHolder));
	_currentFractal = 0;
	this->updateFractalUI();
	chosenDimension = 2;
	b_cameraSizer->Show(false);

	_uiState = AWAITING;

	m_button_beginAnimation->Disable();
}

void MainWindow::onTransformDelete(wxCommandEvent &event)
{
	_fractalControls[_currentFractal].HandleTransformDestroy(event.GetId());
	event.Skip();
}

void MainWindow::onTransformAdd(wxCommandEvent &event)
{
	_fractalControls[_currentFractal].AddLine();
	event.Skip();
}

void MainWindow::fractal_left_button(wxCommandEvent &event)
{
	if (_currentFractal > 0)
	{
		_fractalControls[_currentFractal].Hide();
		_currentFractal--;
		_fractalControls[_currentFractal].Show();
		m_textCtrl7->SetValue("Fraktal " + std::to_string(_currentFractal));
		m_frames->SetValue(std::to_string(_fractalControls[_currentFractal]._framesToNext));
		this->Layout();
	}
}

void MainWindow::fractal_right_button(wxCommandEvent &event)
{
	_fractalControls[_currentFractal].Hide();

	if ((_currentFractal + 1) == _fractalControls.size())
	{
		_fractalControls.push_back(ControlSet(bTransformHolder));
		_currentFractal++;
		_fractalControls[_currentFractal].updateDimensions(chosenDimension);
	}
	else
	{
		_currentFractal++;
		_fractalControls[_currentFractal].Show();
	}
	this->updateFractalUI();
	this->Layout();
}

void MainWindow::on_dimension_pick(wxCommandEvent &event)
{
	// Zmiana wymiaru na nowy
	int newDimension = m_choice1->GetSelection() + 2;
	this->setDimension(newDimension);
}

void MainWindow::setDimension(int newDimension, bool safe)
{
	if (newDimension == chosenDimension)
		return; // Do nothing

	chosenDimension = newDimension;

	_fractalControls[_currentFractal].Hide();
	_fractalControls.clear();

	if (safe) // File loading might want to add its own objects and then modify them
	{
		_fractalControls.push_back(ControlSet(bTransformHolder));
		_fractalControls[_currentFractal].updateDimensions(newDimension);

		this->updateFractalUI();
	}

	_currentFractal = 0;

	if (newDimension == 2)
	{
		b_cameraSizer->Show(false);
	}
	else
	{
		b_cameraSizer->Show(true);
	}

	this->Layout();
}

void MainWindow::updateFractalUI()
{
	m_frames->SetValue(std::to_string(_fractalControls[_currentFractal]._framesToNext));
	m_textCtrl7->SetValue("Fraktal " + std::to_string(_currentFractal));
}

void MainWindow::onAnimateButton(wxCommandEvent &event)
{
	_uiState = PLAYING;
	// m_button_beginAnimation->Disable();
	// m_renderbutton->Disable();
	framesdrawer.draw(data.animation->get_fps(), FramesDrawer::Mode::View);
}

void MainWindow::onGenerateButton(wxCommandEvent &event)
{
	int frame_width;
	int frame_height;
	double fps;
	int iterations;
	////////
	// get time
	m_timetxt->GetValue().ToDouble(&fps);
	//
	// get animation resolution
	m_widthtxt->GetValue().ToInt(&frame_width);
	m_heighttxt->GetValue().ToInt(&frame_height);

	bPanelSizer->SetMinSize(frame_width + 20, frame_height + 20);
	m_fractalPanel->SetMaxSize(wxSize(frame_width, frame_height));
	m_fractalPanel->SetMinSize(wxSize(frame_width, frame_height));
	m_fractalPanel->SetSize(frame_width, frame_height);

	this->Layout();
	this->Fit();
	//
	// get iterations
	m_itertxt->GetValue().ToInt(&iterations);
	////////

	// inicjalizajca sciezki animacji
	std::unique_ptr<AnimationPath> path = std::make_unique<AnimationPath>();

	int gatheredFractals = 0;

	// cammera x, y, z
	double x, y, z;
	m_textCtrl_X->GetValue().ToDouble(&x);
	m_textCtrl_Y->GetValue().ToDouble(&y);
	m_textCtrl_Z->GetValue().ToDouble(&z);

	if (chosenDimension == 2)
	{
		// Buduje wektor Transform_2D eksportuj�c dane z UI
		for (int i = 0; i < _fractalControls.size(); i++)
		{
			std::vector<AffineTransformation_3D> transforms;
			try
			{
				std::vector<AffineTransformation_2D> transforms_2d;
				transforms_2d = _fractalControls[i].exportTransforms2D();
				for (auto &tr : transforms_2d)
					transforms.push_back(tr);
			}
			catch (BadUserInput except)
			{
				return;
			}

			if (transforms.size())
			{
				if (i != 0)
				{
					path->add(std::make_unique<AffineFractal::Parameters>(AffineFractal::Parameters(glm::vec3(x, y, z), transforms)), _fractalControls[i - 1]._framesToNext / fps);
				}

				else
				{
					path->add(std::make_unique<AffineFractal::Parameters>(AffineFractal::Parameters(glm::vec3(x, y, z), transforms)), 0);
				}
				gatheredFractals++;
			}
			else
				break; // Ostatni fraktal w UI bez transformacji to koniec animacji, lub jezeli skonczly sie fraktale
		}

		if (gatheredFractals < 2)
			return; // Nie da sie zrobic animacji z jednego fraktala
	}
	else if (chosenDimension == 3)
	{
		// Buduje wektor Transform_2D eksportuj�c dane z UI
		for (int i = 0; i < _fractalControls.size(); i++)
		{
			std::vector<AffineTransformation_3D> transforms;
			try
			{
				transforms = _fractalControls[i].exportTransforms3D();
			}
			catch (BadUserInput except)
			{
				return;
			}

			if (transforms.size())
			{
				if (i != 0)
				{
					path->add(std::make_unique<AffineFractal::Parameters>(AffineFractal::Parameters(glm::vec3(x, y, z), transforms)), _fractalControls[i - 1]._framesToNext / fps);
				}
				else
				{
					path->add(std::make_unique<AffineFractal::Parameters>(AffineFractal::Parameters(glm::vec3(x, y, z), transforms)), 0);
				}
				gatheredFractals++;
			}
			else
				break; // Ostatni fraktal w UI bez transformacji to koniec animacji, lub jezeli skonczly sie fraktale
		}

		if (gatheredFractals < 2)
			return; // Nie da sie zrobic animacji z jednego fraktala
	}

	std::unique_ptr<FractalGenerator::Points> points = std::make_unique<AffineFractal::PointsGenerator>(iterations); // w tym wypadku argumentem jest ilosc iteracji
	std::unique_ptr<FractalGenerator::Pixels> pixels = std::make_unique<PointScatter>(1);							 // z_shadow

	// Animation initialization
	data.animation = std::make_unique<Animation>(
		std::move(path),   // AnimationPath
		std::move(points), // Inheritance of FractalGenerator::Points
		std::move(pixels)  // Inheritance of FractalGenerator::Pixels
						   // TODO: post_process_stack
	);

	try
	{
		data.animation->render(fps, -1, frame_width, frame_height); // fps, n_of_threads, W, H
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

	_timer->Start(100);
	_uiState = RENDERING;
	// m_renderbutton->Disable();
	m_button_beginAnimation->Disable();

	framesdrawer.draw(30, FramesDrawer::Mode::Render);
	event.Skip();
}

void MainWindow::onFramesText(wxCommandEvent &event)
{

	int val;
	if (m_frames->GetValue().ToInt(&val))
		_fractalControls[_currentFractal]._framesToNext = val;
}

void MainWindow::onTimer(wxCommandEvent &event)
{
	int total = data.animation->n_frames();

	switch (_uiState)
	{
	case AWAITING:
		break;
	case RENDERING:
		m_progress->SetValue((static_cast<float>(framesdrawer.current_frame) / total) * 100.0);
		if (framesdrawer.current_frame == total)
		{
			_uiState = AWAITING;
			m_button_beginAnimation->Enable();
			m_renderbutton->Enable();
			_timer->Stop();
		}
		break;
	case PLAYING:
		m_progress->SetValue((static_cast<float>(framesdrawer.current_frame) / total) * 100.0);
		if (framesdrawer.current_frame == total)
		{
			_uiState = AWAITING;
			m_button_beginAnimation->Enable();
			m_renderbutton->Enable();
			_timer->Stop();
		}
		break;
	}
}