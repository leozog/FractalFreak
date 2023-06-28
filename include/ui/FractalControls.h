#pragma once

#include "BaseFrame.h"

// Represents a control set for specifying fractal parameters
class ControlLine
{

	friend class ControlSet;

public:
	// Construct a new line set to add to the parent container
	ControlLine(wxSizer * container, int dimensions = 2) : _parentContainer(container), _dimensions(dimensions)
	{
		// Create a sizer to store buttons in
		_myLineSizer = new wxBoxSizer(wxHORIZONTAL);
		_parentContainer->Insert(_parentContainer->GetItemCount() - 1, _myLineSizer, 0, wxEXPAND, 5);

		// Button used for deleting the transform
		_myDeleteButton = new wxButton(_parentContainer->GetContainingWindow(), wxID_ANY, wxT("-"), wxDefaultPosition, wxDefaultSize, 0);
		_myLineSizer->Add(_myDeleteButton, 0, wxALL, 5);


		for (int i = 0; i < dimensions * (dimensions + 1); i++) // TODO: Update this to N dimensions
		{
			wxTextCtrl* m_textctrl = new wxTextCtrl(_parentContainer->GetContainingWindow(), wxID_ANY, wxT("1"), wxDefaultPosition, wxDefaultSize, wxTE_CENTER);
			m_textctrl->SetMaxSize(wxSize(40, -1));
			_myLineSizer->Add(m_textctrl, 0, wxALL, 5);
			_myInputs.push_back(m_textctrl);
		}

		_parentContainer->Layout();

		_myDeleteButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::onTransformDelete), NULL, _parentContainer->GetContainingWindow());

	}

	// Creating copies of the controlline objects would cause a ton of issues in terms of wxwidgets
	ControlLine(const ControlLine& other) = delete;
	ControlLine & operator=(const ControlLine& other) = delete;


	ControlLine(ControlLine&& other)
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

	ControlLine& operator=(ControlLine&& other)
	{
		if (this == &other) return *this;

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
			_myDeleteButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::onTransformDelete), NULL, _parentContainer->GetContainingWindow());
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
	wxSizer* _parentContainer;
	wxBoxSizer* _myLineSizer;
	wxButton* _myDeleteButton;
	std::vector<wxTextCtrl*> _myInputs;
	int _dimensions;
};


class ControlSet
{
public:
	// Construct a new Control Set, it requires a container to write to and can be set to not render when created
	ControlSet(wxSizer * container, int dimensions = 2, bool startHidden = false) : _parentContainer(container), _hidden(startHidden), _dimensions(dimensions)
	{

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
		_lines.push_back(ControlLine(_parentContainer, _dimensions));
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
	/* std::vector<Transformation> exportTransforms()
	{
		std::vector<Transformation> _toReturn;
		for (int i = 0; i < _lines.size(); i++)
		{
			const int currentDimension = _lines[i]._dimensions;
			_toReturn.push_back(Transformation(_lines[i]._dimensions));
			for (int j = 0; j < currentDimension * (currentDimension + 1); j++)
			{
				_lines[i]._myInputs[j]->GetValue().ToDouble(_toReturn[i]._coefficients + j); // For the love of all stop-signs in the Galaxy, cease and desist
			}
		}
		return _toReturn;
	} */

protected:
	wxSizer* _parentContainer;
	std::vector<ControlLine> _lines;
	bool _hidden;
	int _dimensions;
};