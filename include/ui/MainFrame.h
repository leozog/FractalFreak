#pragma once

#include "BaseFrame.h"
#include "FractalControls.h"
#include <wx/image.h>
#include <wx/dc.h>
#include <wx/dcbuffer.h>
#include "AppData.h"
#include <wx/filedlg.h>
#include <fstream>
#include <sstream>

/**
 * @brief Główny obiekt wxFrame odpowiedzialny za kontrolę przepływu informacji przez program
 *
 */
class MainFrame : public MyFrame1
{

protected:
	/**
	 * @brief Metoda przewijająca selekcję wyświetlanego fraktalu w lewo
	 *
	 * @param event
	 */
	void fractal_left_button(wxCommandEvent &event) override;

	/**
	 * @brief Metoda przewijająca selekcję wyświetlanego fraktalu w prawo. Dodaje nowy fraktal jeżeli nie istnieje
	 *
	 * @param event
	 */
	void fractal_right_button(wxCommandEvent &event) override;

	/**
	 * @brief Metoda obsługująca zdarzenie wyboru wymiaru animacji
	 *
	 * @param event
	 */
	void on_dimension_pick(wxCommandEvent &event) override;

	/**
	 * @brief Metoda obsługująca zdarzenie kliknięcia w przycisk rozpoczęcia wyświetlania animacji
	 *
	 * @param event
	 */
	void onAnimateButton(wxCommandEvent &event) override;

	/**
	 * @brief Metoda obsługująca zdarzenie kliknięcia w przycisk rozpoczęcia generowania animacji
	 *
	 * @param event
	 */
	void onGenerateButton(wxCommandEvent &event) override;

	/**
	 * @brief Metoda obsługująca zdarzenie kliknięcia w toolbar otwarcia pliku
	 *
	 * @param event
	 */
	void onFileLoad(wxCommandEvent &event) override;

	/**
	 * @brief Metoda obsługująca zdarzenie wpisania tekstu do kontroli ilości klatek fraktala
	 *
	 * @param event
	 */
	void onFramesText(wxCommandEvent &event) override;

	/**
	 * @brief Wyświetla klatkę animacji przesłaną jako obiekt wxImage w panelu
	 *
	 * @param img
	 */
	void drawFrame(wxImage img);

	int _currentFractal; // Obecnie wybrany fraktal

	std::vector<ControlSet> _fractalControls; // Wektor wszystkich fraktali i ich obiektów kontrolnych

	AppData &data; // Obiekt przechowujący odwołanie do kontrolera animacji

public:
	/**
	 * @brief Construct a new Main Frame object
	 *
	 * @param parent wskaźnik do okna
	 * @param _dataRef referencja do obiektu danych programu
	 */
	MainFrame(wxWindow *parent, AppData &_dataRef);

	/**
	 * @brief Destroy the Main Frame object
	 *
	 */
	~MainFrame(){};

	/**
	 * @brief Metoda obsługująca usunięcie transformacji, przekazuje wydarzenie dalej do kontrolerów
	 *
	 * @param event
	 */
	void onTransformDelete(wxCommandEvent &event) override;

	/**
	 * @brief Metoda obsługująca dodanie nowej transformacji do obecnie wybranego fraktala
	 *
	 * @param event
	 */
	void onTransformAdd(wxCommandEvent &event) override;

	/**
	 * @brief Metoda obsługująca wyświetlenie obrazu wxImage przesłanego przez wskaźnik
	 *
	 * @param img
	 */
	void drawFrame(std::shared_ptr<wxImage> img);
};