#include "Application.h"
#include "Frame.h"

wxIMPLEMENT_APP(Application);

Application::Application()
{
	this->frame = nullptr;
}

/*virtual*/ Application::~Application()
{
}

/*virtual*/ bool Application::OnInit()
{
	if (!wxApp::OnInit())
		return false;

	this->frame = new Frame(wxDefaultPosition, wxSize(2000, 1500));
	this->frame->Show();

	return true;
}

/*virtual*/ int Application::OnExit()
{
	if (this->gameThread.IsRunning())
		this->gameThread.Join();

	return 0;
}

GameThread* Application::GetGameThread()
{
	return &this->gameThread;
}