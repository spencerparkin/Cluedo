#pragma once

#include "Card.h"
#include <string>

class Player
{
	friend class Game;

public:
	Player(const std::string& name);
	virtual ~Player();

	const std::string& GetName() const;

	virtual void TakePossessionOfCard(const Card& card) = 0;
	virtual int GetTotalCardsInPossession() const = 0;
	virtual void BeIntroducedTo(const Player* player);
	virtual void PrepareForGame();
	virtual bool SolveMurderMsytery(Accusation& accustaion);
	virtual void MakeAccusation(Accusation& accusation) = 0;
	virtual Room GetDesiredRoom() = 0;
	virtual bool RefuteAccusation(const Accusation& accusation, const Player* accuser, Card& cardToShowAccuser) = 0;
	virtual void PlayerCouldNotRefuteAccusation(const Player* player, const Accusation& accusation, const Player* accuser);
	virtual void AccusationDisproved(const Accusation& accusation, const Player* disprover, const Card* cardOwnedByDisprover);
	virtual void AccusationCouldNotBeRefutedByAnyone(const Accusation& accusation, const Player* accuser);

private:
	bool isDisqualified;
	std::string name;
};