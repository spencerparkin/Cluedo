#include "Frame.h"
#include "Canvas.h"
#include <wx/menu.h>
#include <wx/sizer.h>
#include <wx/aboutdlg.h>

Frame::Frame(const wxPoint& pos, const wxSize& size) : wxFrame(nullptr, wxID_ANY, wxT("Cluedo"), pos, size)
{
	wxMenu* gameMenu = new wxMenu();
	gameMenu->Append(new wxMenuItem(gameMenu, ID_Connect, "Connect", "Connect to a game server."));
	gameMenu->Append(new wxMenuItem(gameMenu, ID_Disconnect, "Disconnect", "Disconnect from the game server."));
	gameMenu->AppendSeparator();
	gameMenu->Append(new wxMenuItem(gameMenu, ID_Exit, "Exit", "Close this program."));

	wxMenu* helpMenu = new wxMenu();
	helpMenu->Append(new wxMenuItem(helpMenu, ID_About, "About", "Show the about box."));

	wxMenuBar* menuBar = new wxMenuBar();
	menuBar->Append(gameMenu, "Game");
	menuBar->Append(helpMenu, "Help");
	this->SetMenuBar(menuBar);

	this->Bind(wxEVT_MENU, &Frame::OnConnect, this, ID_Connect);
	this->Bind(wxEVT_MENU, &Frame::OnDisconnect, this, ID_Disconnect);
	this->Bind(wxEVT_MENU, &Frame::OnExit, this, ID_Exit);
	this->Bind(wxEVT_MENU, &Frame::OnAbout, this, ID_About);
	this->Bind(wxEVT_UPDATE_UI, &Frame::OnUpdateUI, this, ID_Connect);
	this->Bind(wxEVT_UPDATE_UI, &Frame::OnUpdateUI, this, ID_Disconnect);

	this->SetStatusBar(new wxStatusBar(this));

	this->canvas = new Canvas(this);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(this->canvas, 1, wxALL | wxGROW, 0);
	this->SetSizer(mainSizer);
}

/*virtual*/ Frame::~Frame()
{
}

void Frame::OnConnect(wxCommandEvent& event)
{
}

void Frame::OnDisconnect(wxCommandEvent& event)
{
}

void Frame::OnExit(wxCommandEvent& event)
{
	this->Close(true);
}

void Frame::OnAbout(wxCommandEvent& event)
{
	wxAboutDialogInfo aboutDialogInfo;

	aboutDialogInfo.SetName("Cluedo");
	aboutDialogInfo.SetDescription("This program is designed to be a game client for the classic game of clue.");

	wxAboutBox(aboutDialogInfo);
}

void Frame::OnUpdateUI(wxUpdateUIEvent& event)
{
	switch (event.GetId())
	{
		case ID_Connect:
		{
			break;
		}
		case ID_Disconnect:
		{
			break;
		}
	}
}