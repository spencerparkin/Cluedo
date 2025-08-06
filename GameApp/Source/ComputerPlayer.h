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

// Your memory is in two parts A and B...
// 
// A: For each card you track the set of possible owners.  (If a singleton, you know the owner.)
//
// B: You also track all refutes.  (e.g., Sally disproved an accusation.  We're not told how, but we know she did.)
//
// Anytime the state of A changes, you can reduce B.
// Reducing B can change the state of A.
//
// When a failure to refute occurs, you can update A.
//
// A refute is reduced when we know that the disprover doesn't have a card in the disproved accusation.
// When a refute reduces to one card, then we know the disprover has that card.
//
// And of course, we can change A whenever we make an accusation and either receive a refute of it or someone fails to refute it.
//
// A note about updating A: We also know the total number of cards in everyone's hand, and that never changes.
// Therefore, if the total number of remaining unknown cards in a person's hand equals the total number of possible
// cards the person is assigned to, then we can deduce that they have those cards.