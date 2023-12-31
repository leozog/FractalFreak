#pragma once

#include "MyWindow.h"
#include "FractalsDefinitions.h"

// Represents a control set for specifying fractal parameters
class ControlLine
{

	friend class ControlSet;

public:
	// Construct a new line set to add to the parent container
	ControlLine(wxSizer *container, int dimensions = 2, bool doNotShow = false) : _parentContainer(container), _dimensions(dimensions)
	{
		// Create a sizer to store buttons in
		_myLineSizer = new wxBoxSizer(wxHORIZONTAL);
		_parentContainer->Insert(_parentContainer->GetItemCount() - 1, _myLineSizer, 0, wxEXPAND, 5);

		// Button used for deleting the transform
		_myDeleteButton = new wxButton(_parentContainer->GetContainingWindow(), wxID_ANY, wxT("-"), wxDefaultPosition, wxDefaultSize, 0);
		_myLineSizer->Add(_myDeleteButton, 0, wxALL, 5);

		for (int i = 0; i < dimensions * (dimensions + 1); i++) // TODO: Update this to N dimensions
		{
			wxTextCtrl *m_textctrl = new wxTextCtrl(_parentContainer->GetContainingWindow(), wxID_ANY, wxT("1"), wxDefaultPosition, wxDefaultSize, wxTE_CENTER);
			m_textctrl->SetMaxSize(wxSize(40, -1));
			_myLineSizer->Add(m_textctrl, 0, wxALL, 5);
			_myInputs.push_back(m_textctrl);
		}

		_parentContainer->Layout();

		_myLineSizer->Show(!doNotShow);

		_myDeleteButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyWindow::onTransformDelete), NULL, _parentContainer->GetContainingWindow());
	}

	// Creating copies of the controlline objects would cause a ton of issues in terms of wxwidgets
	ControlLine(const ControlLine &other) = delete;
	ControlLine &operator=(const ControlLine &other) = delete;

	ControlLine(ControlLine &&other)
	{
		_myLineSizer = other._myLineSizer;
		other._myLineSizer = nullptr;

		_myDeleteButton = other._myDeleteButton;
		other._myDeleteButton = nullptr;

		_myInputs = std::move(other._myInputs);
		other._myInputs.clear();

		_parentContainer = other._parentContainer;
		other._parentContainer = nullptr;

		_dimensions = other._dimensions;
	}

	ControlLine &operator=(ControlLine &&other)
	{
		if (this == &other)
			return *this;

		this->~ControlLine();

		_myLineSizer = other._myLineSizer;
		other._myLineSizer = nullptr;

		_myDeleteButton = other._myDeleteButton;
		other._myDeleteButton = nullptr;

		_myInputs = std::move(other._myInputs);
		other._myInputs.clear();

		_parentContainer = other._parentContainer;
		other._parentContainer = nullptr;

		_dimensions = other._dimensions;

		return *this;
	}

	// Hide all elements of the line without destroying them
	void Hide()
	{
		_parentContainer->Show(_myLineSizer, false, true);
	}

	// Show all elements of the line
	void Show()
	{
		_parentContainer->Show(_myLineSizer, true, true);
	}

	void updateDimensions(int newDimensions)
	{
		// It's not a bug... It's a feature!
		/*
		if (newDimensions > _dimensions)
		{
			int controlsToCreate = newDimensions * (newDimensions + 1) - _myInputs.size();

		}
		*/
	}

	~ControlLine()
	{
		if (_myDeleteButton)
		{
			_myDeleteButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyWindow::onTransformDelete), NULL, _parentContainer->GetContainingWindow());
			_myDeleteButton->Hide(); // TODO: Button garbage collection (help me God)
		}

		for (int i = 0; i < _myInputs.size(); i++)
		{
			_myInputs[i]->Destroy();
		}

		if (_parentContainer && _myLineSizer)
		{
			_parentContainer->Remove(_myLineSizer);
		}

		if (_parentContainer)
		{
			_parentContainer->Layout();
		}
	}

private:
	wxSizer *_parentContainer;
	wxBoxSizer *_myLineSizer;
	wxButton *_myDeleteButton;
	std::vector<wxTextCtrl *> _myInputs;
	int _dimensions;
};

class BadUserInput : public std::exception {
public:
	BadUserInput(int input, int transform) : _input(input), _transform(transform) {}
	const char* what(){
		return "bad user arguments were provided";
		}
	int _input;
	int _transform;
};

class ControlSet
{
public:
	// Construct a new Control Set, it requires a container to write to and can be set to not render when created
	ControlSet(wxSizer *container, int dimensions = 2, bool startHidden = false) : _parentContainer(container), _hidden(startHidden), _dimensions(dimensions)
	{
		_framesToNext = 10;
	}

	// Show the entire control set again
	void Show()
	{
		_hidden = false;
		for (int i = 0; i < _lines.size(); i++)
		{
			_lines[i].Show();
		}
		_parentContainer->GetContainingWindow()->Layout();
	}

	// Hide the entire control set without destroying its controls
	void Hide()
	{
		_hidden = true;
		for (int i = 0; i < _lines.size(); i++)
		{
			_lines[i].Hide();
		}
		_parentContainer->GetContainingWindow()->Layout();
	}

	// Add a new line to the mix
	void AddLine()
	{
		_lines.push_back(ControlLine(_parentContainer, _dimensions, _hidden));
		_parentContainer->GetContainingWindow()->Layout();
	}

	// Accepts a destroy event from the deletion buttons and figures out which line needs to be erased from existence
	void HandleTransformDestroy(wxWindowID deleteID)
	{
		for (int i = 0; i < _lines.size(); i++)
		{
			if (_lines[i]._myDeleteButton->GetId() == deleteID)
			{
				_lines.erase(_lines.begin() + i);
				break;
			}
		}
	}

	void updateDimensions(int newDimensions)
	{
		_dimensions = newDimensions;
		/// TODO
	}

	// Exportts all transformations into something more manageable
	std::vector<AffineTransformation_2D> exportTransforms2D()
	{
		std::vector<AffineTransformation_2D> _toReturn;
		for (int i = 0; i < _lines.size(); i++)
		{
			const int currentDimension = _lines[i]._dimensions;
			double a, b, c, d, e, f;
			if (!_lines[i]._myInputs[0]->GetValue().ToCDouble(&a))
			{
				throw BadUserInput(0, i);
			}
			if (!_lines[i]._myInputs[1]->GetValue().ToCDouble(&b))
			{
				throw BadUserInput(1, i);
			}
			if (!_lines[i]._myInputs[2]->GetValue().ToCDouble(&c))
			{
				throw BadUserInput(2, i);
			}
			if (!_lines[i]._myInputs[3]->GetValue().ToCDouble(&d))
			{
				throw BadUserInput(3, i);
			}
			if (!_lines[i]._myInputs[4]->GetValue().ToCDouble(&e))
			{
				throw BadUserInput(4, i);
			}
			if (!_lines[i]._myInputs[5]->GetValue().ToCDouble(&f))
			{
				throw BadUserInput(5, i);
			}


			_toReturn.push_back(AffineTransformation_2D(a, b, c, d, e, f));
		}
		return _toReturn;
	}

	std::vector<AffineTransformation_3D> exportTransforms3D()
	{
		std::vector<AffineTransformation_3D> _toReturn;
		for (int i = 0; i < _lines.size(); i++)
		{
			const int currentDimension = _lines[i]._dimensions;
			double a, b, c, d, e, f, g, h, v, j, k, l;
			if (!_lines[i]._myInputs[0]->GetValue().ToCDouble(&a))
			{
				throw BadUserInput(0, i);
			}
			if (!_lines[i]._myInputs[1]->GetValue().ToCDouble(&b))
			{
				throw BadUserInput(1, i);
			}
			if (!_lines[i]._myInputs[2]->GetValue().ToCDouble(&c))
			{
				throw BadUserInput(2, i);
			}
			if (!_lines[i]._myInputs[3]->GetValue().ToCDouble(&d))
			{
				throw BadUserInput(3, i);
			}
			if (!_lines[i]._myInputs[4]->GetValue().ToCDouble(&e))
			{
				throw BadUserInput(4, i);
			}
			if (!_lines[i]._myInputs[5]->GetValue().ToCDouble(&f))
			{
				throw BadUserInput(5, i);
			}
			if (!_lines[i]._myInputs[6]->GetValue().ToCDouble(&g))
			{
				throw BadUserInput(65, i);
			}
			if (!_lines[i]._myInputs[7]->GetValue().ToCDouble(&h))
			{
				throw BadUserInput(7, i);
			}
			if (!_lines[i]._myInputs[8]->GetValue().ToCDouble(&v))
			{
				throw BadUserInput(8, i);
			}
			if (!_lines[i]._myInputs[9]->GetValue().ToCDouble(&j))
			{
				throw BadUserInput(9, i);
			}
			if (!_lines[i]._myInputs[10]->GetValue().ToCDouble(&k))
			{
				throw BadUserInput(10, i);
			}
			if (!_lines[i]._myInputs[11]->GetValue().ToCDouble(&l))
			{
				throw BadUserInput(11, i);
			}


			_toReturn.push_back(AffineTransformation_3D(a, b, c, d, e, f, g, h, v, j, k, l));
		}
		return _toReturn;
	}

	std::string to_string() const
	{
		std::string toReturn = std::to_string(_lines.size()) + "\n";
		for (int i = 0; i < _lines.size(); i++)
		{
			for (int j = 0; j < (_dimensions * (_dimensions + 1) - 1); j++)
			{
				toReturn += _lines[i]._myInputs[j]->GetValue() + " ";
			}
			toReturn += _lines[i]._myInputs[_dimensions * (_dimensions + 1) - 1]->GetValue() + "\n";
		}
		toReturn += std::to_string(_framesToNext);
		return toReturn;
	}

	// Ustawia tekst w �rodku linii, do u�ycia przy importowaniu
	void setLine(std::vector<std::string> &values, int index)
	{
		for (int i = 0; i < values.size(); i++)
		{
			_lines[index]._myInputs[i]->SetValue(values[i]);
		}
	}

	int _framesToNext;

protected:
	wxSizer *_parentContainer;
	std::vector<ControlLine> _lines;
	bool _hidden;
	int _dimensions;
};