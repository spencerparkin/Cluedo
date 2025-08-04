#pragma once

#include "Player.h"

class ComputerPlayer : public Player
{
public:
	ComputerPlayer(const std::string& name);
	virtual ~ComputerPlayer();

	virtual void Participate(CluedoGame* game) override;
};