#include "ComputerPlayer.h"

ComputerPlayer::ComputerPlayer(const std::string& name) : Player(name)
{
}

/*virtual*/ ComputerPlayer::~ComputerPlayer()
{
}

/*virtual*/ void ComputerPlayer::TakePossessionOfCard(const Card& card)
{
}

/*virtual*/ int ComputerPlayer::GetTotalCardsInPossession() const
{
	return 0;
}

/*virtual*/ void ComputerPlayer::BeIntroducedTo(const Player* player)
{
}

/*virtual*/ void ComputerPlayer::PrepareForGame()
{
}

/*virtual*/ Room ComputerPlayer::GetDesiredRoom()
{
	return Room::BallRoom;
}

/*virtual*/ void ComputerPlayer::MakeAccusation(Accusation& accusation)
{
}

/*virtual*/ bool ComputerPlayer::RefuteAccusation(const Accusation& accusation, const Player* accuser, Card& cardToShowAccuser)
{
	return false;
}

/*virtual*/ void ComputerPlayer::PlayerCouldNotRefuteAccusation(const Player* player, const Accusation& accusation, const Player* accuser)
{
}

/*virtual*/ void ComputerPlayer::AccusationDisproved(const Accusation& accusation, const Player* disprover, const Card* cardOwnedByDisprover)
{
}

/*virtual*/ void ComputerPlayer::AccusationCouldNotBeRefutedByAnyone(const Accusation& accusation, const Player* accuser)
{
}