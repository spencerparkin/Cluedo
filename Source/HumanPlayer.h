#pragma once

#include "Player.h"

class HumanPlayer : public Player
{
public:
	HumanPlayer(const std::string& name);
	virtual ~HumanPlayer();

	virtual void TakePossessionOfCard(const Card& card) override;
	virtual Room GetDesiredRoom() override;
	virtual void MakeAccusation(Accusation& accusation) override;
};