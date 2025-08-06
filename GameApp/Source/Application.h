#pragma once

#include "Game.h"
#include <wx/app.h>
#include <mutex>

class Frame;

class Application : public wxApp
{
public:
	Application();
	virtual ~Application();

	virtual bool OnInit() override;
	virtual int OnExit() override;

	Game* GetGame();

private:

	Frame* frame;

	Game game;
};

wxDECLARE_APP(Application);