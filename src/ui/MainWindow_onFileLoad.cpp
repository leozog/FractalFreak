#include "ui/MainWindow.h"

void MainWindow::onFileLoad(wxCommandEvent &event)
{
	// Aby zaladowac plik potrzebny jest plik
	wxFileDialog
		openFileDialog(this, _("Otworz plik tekstowy z fraktalem"), "", "",
					   "TXT z fraktalem (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return; // the user changed idea...

	std::ifstream input;
	input.open(openFileDialog.GetPath().ToStdString());

	// Pierwsza linia to rozmiar, iteracje, typ
	std::string firstLine;
	getline(input, firstLine);

	std::stringstream processing(firstLine);

	std::string elem;

	// Width
	getline(processing, elem, ',');
	m_widthtxt->SetValue(elem);

	// Height
	getline(processing, elem, ',');
	m_heighttxt->SetValue(elem);

	// Iteracje
	getline(processing, elem, ',');
	m_itertxt->SetValue(elem);

	// Wymiar
	getline(processing, elem, ',');
	int dimensions = std::atoi(elem.data());

	int dimensionsNormal = dimensions + 2;

	m_choice1->SetSelection(dimensions);
	this->setDimension(dimensionsNormal, false);
	

	// Kolejna linia to pozycja kamery
	getline(input, elem); // pomin pozycje kamery

	processing = std::stringstream(elem);

	getline(processing, elem, ' ');
	m_textCtrl_X->SetValue(elem);

	getline(processing, elem, ' ');
	m_textCtrl_X->SetValue(elem);

	getline(processing, elem, ' ');
	m_textCtrl_X->SetValue(elem);

	// Kolejna linia to liczba fraktali do wczytania
	getline(input, elem);
	int fractals = std::atoi(elem.data());

	_fractalControls.clear();
	_currentFractal = 0;

	

	// Wczytywanie fraktali
	for (int i = 0; i < fractals; i++)
	{
		// Ta linia to liczba transformacji we fraktalu
		getline(input, elem);
		int transforms = std::atoi(elem.data());
		_fractalControls.push_back(ControlSet(bTransformHolder, dimensionsNormal, true));

		// Teraz odczytywane sa kolejne transformacje
		for (int j = 0; j < transforms; j++)
		{
			_fractalControls[i].AddLine();

			getline(input, elem); // transformacja
			std::stringstream transform(elem);

			std::vector<std::string> inputs;

			// Tyle cyferek ile dyktuje  -- rozmiar * rozmiar + wyraz wolny wspolczynnikow
			for (int k = 0; k < (dimensionsNormal) * (dimensionsNormal + 1) ; k++)
			{
				getline(transform, elem, ' ');
				inputs.push_back(elem);
			}

			_fractalControls[i].setLine(inputs, j);
		}

		if (i != fractals - 1)
		{
			getline(input, elem);
			_fractalControls[i]._framesToNext = std::atoi(elem.data()); // frames
		}
		else
		{
			_fractalControls[i]._framesToNext = 0;
		}
		
	}

	_currentFractal = 0;
	_fractalControls[0].Show();
	this->updateFractalUI();
	this->Layout();
	
}