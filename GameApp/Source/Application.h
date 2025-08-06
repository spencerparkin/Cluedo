#pragma once

#include "GameState.h"
#include <wx/app.h>

class Frame;

class Application : public wxApp
{
public:
	Application();
	virtual ~Application();

	virtual bool OnInit() override;
	virtual int OnExit() override;

	Cluedo::BoardGraph* GetBoardGraph();

private:

	Cluedo::GameState gameState;

	Frame* frame;
};

wxDECLARE_APP(Application);