#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(const std::string& name) : Player(name)
{
}

/*virtual*/ HumanPlayer::~HumanPlayer()
{
}

/*virtual*/ void HumanPlayer::TakePossessionOfCard(const Card& card)
{
}

/*virtual*/ Room HumanPlayer::GetDesiredRoom()
{
	return Room::BallRoom;
}

/*virtual*/ void HumanPlayer::MakeAccusation(Accusation& accusation)
{
}