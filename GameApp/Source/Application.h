#pragma once

#include "GameThread.h"
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

	GameThread* GetGameThread();

private:

	Frame* frame;

	GameThread gameThread;
};

wxDECLARE_APP(Application);