#include "ui/MainWindow.h"

void MainWindow::onFileLoad(wxCommandEvent &event)
{
	wxFileDialog
		openFileDialog(this, _("Otworz plik tekstowy z fraktalem"), "", "",
					   "TXT z fraktalem (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return; // the user changed idea...

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
	m_itertxt->SetValue(elem);

	getline(processing, elem, ',');
	int dimensions = std::atoi(elem.data());

	_fractalControls[_currentFractal].Hide();
	_fractalControls.clear();
	_currentFractal = 0;

	if (dimensions == 0)
	{

		getline(input, elem); // pomin pozycje kamery
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

			getline(input, elem);
			_fractalControls[i]._framesToNext = std::atoi(elem.data()); // frames

			if (i == 0)
			{
				_fractalControls[0].Show();
				m_frames->SetValue(elem);
			}
		}
	}
}