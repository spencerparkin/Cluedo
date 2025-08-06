#include "GameThread.h"

GameThread::GameThread()
{
}

/*virtual*/ GameThread::~GameThread()
{
}

/*virtual*/ bool GameThread::Split()
{
	//...

	return Thread::Split();
}

/*virtual*/ bool GameThread::Join()
{
	// TODO: Signal exit here.  Tell the game that we need to exit.

	return Thread::Join();
}

Game* GameThread::GetGame()
{
	return &this->game;
}

/*virtual*/ void GameThread::Run()
{
	this->game.Play();
}