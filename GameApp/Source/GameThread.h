#pragma once

#include "Game.h"
#include "Thread.h"

class GameThread : public Thread
{
public:
	GameThread();
	virtual ~GameThread();

	virtual bool Split() override;
	virtual bool Join() override;

	Game* GetGame();

private:
	virtual void Run() override;

	Game game;
};