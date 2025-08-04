#pragma once

#include "Player.h"

class HumanPlayer : public Player
{
public:
	HumanPlayer(const std::string& name);
	virtual ~HumanPlayer();
};