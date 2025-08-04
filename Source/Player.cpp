#include "Player.h"

Player::Player(const std::string& name)
{
	this->isDisqualified = false;
	this->name = name;
}

/*virtual*/ Player::~Player()
{
}

const std::string& Player::GetName() const
{
	return this->name;
}

/*virtual*/ void Player::BeIntroducedTo(const Player* player)
{
}

/*virtual*/ void Player::PrepareForGame()
{
}

/*virtual*/ bool Player::SolveMurderMsytery(Accusation& accustaion)
{
	return false;
}

/*virtual*/ void Player::PlayerCouldNotRefuteAccusation(const Player* player, const Accusation& accusation, const Player* accuser)
{
}

/*virtual*/ void Player::AccusationDisproved(const Accusation& accusation, const Player* disprover, const Card* cardOwnedByDisprover)
{
}

/*virtual*/ void Player::AccusationCouldNotBeRefutedByAnyone(const Accusation& accusation, const Player* accuser)
{
}