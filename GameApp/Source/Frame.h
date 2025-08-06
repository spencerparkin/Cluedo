#pragma once

#include <wx/frame.h>

class Canvas;

class Frame : public wxFrame
{
public:
	Frame(const wxPoint& pos, const wxSize& size);
	virtual ~Frame();

	enum
	{
		ID_Connect = wxID_HIGHEST,
		ID_Disconnect,
		ID_Exit,
		ID_About
	};

	void OnConnect(wxCommandEvent& event);
	void OnDisconnect(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnUpdateUI(wxUpdateUIEvent& event);

private:

	Canvas* canvas;
};