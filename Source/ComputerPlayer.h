#pragma once

#include "Player.h"

class ComputerPlayer : public Player
{
public:
	ComputerPlayer(const std::string& name);
	virtual ~ComputerPlayer();

	virtual void TakePossessionOfCard(const Card& card) override;
	virtual int GetTotalCardsInPossession() const override;
	virtual void BeIntroducedTo(const Player* player) override;
	virtual void PrepareForGame() override;
	virtual Room GetDesiredRoom() override;
	virtual void MakeAccusation(Accusation& accusation) override;
	virtual bool RefuteAccusation(const Accusation& accusation, const Player* accuser, Card& cardToShowAccuser) override;
	virtual void PlayerCouldNotRefuteAccusation(const Player* player, const Accusation& accusation, const Player* accuser) override;
	virtual void AccusationDisproved(const Accusation& accusation, const Player* disprover, const Card* cardOwnedByDisprover) override;
	virtual void AccusationCouldNotBeRefutedByAnyone(const Accusation& accusation, const Player* accuser) override;
};