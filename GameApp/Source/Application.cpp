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
	return 0;
}

Cluedo::BoardGraph* Application::GetBoardGraph()
{
	return this->gameState.GetBoardGraph();
}