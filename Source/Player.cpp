#include "Player.h"

Player::Player(const std::string& name)
{
	this->name = name;
	this->isDisqualified = false;
}

/*virtual*/ Player::~Player()
{
}

void Player::AddCard(std::shared_ptr<Card> card)
{
	this->cardArray.push_back(card);
}

int Player::GetNumCards() const
{
	return (int)this->cardArray.size();
}

void Player::SetDisqualfiied(bool isDisqualified)
{
	this->isDisqualified = isDisqualified;
}

bool Player::IsDisqualified() const
{
	return this->isDisqualified;
}

const std::string& Player::GetName() const
{
	return this->name;
}