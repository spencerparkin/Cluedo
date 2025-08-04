#include "Player.h"

Player::Player(const std::string& name)
{
	this->name = name;
}

/*virtual*/ Player::~Player()
{
}

const std::string& Player::GetName() const
{
	return this->name;
}