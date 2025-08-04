#include "CluedoGame.h"
#include "Player.h"
#include <stdio.h>

CluedoGame::CluedoGame()
{
}

/*virtual*/ CluedoGame::~CluedoGame()
{
}

bool CluedoGame::AddPlayer(std::shared_ptr<Player> player)
{
	for (std::shared_ptr<Player> existingPlayer : this->playerArray)
		if (existingPlayer->GetName() == player->GetName())
			return false;

	this->playerArray.push_back(player);
	return true;
}

void CluedoGame::Play()
{
	if (this->playerArray.size() < 2)
		return;

	this->winner.reset();

	Card::GenerateDeck(this->cardArray);

	std::vector<std::shared_ptr<Card>> dealArray;
	for (std::shared_ptr<Card>& card : this->cardArray)
		dealArray.push_back(card);

	Card::ShuffleCards(dealArray);

	// Determine the mystery.
	this->murderMystery.murderWeapon = Card::FindAndRemoveCardOfTypeFromDeck(dealArray, Card::Type::Weapon);
	this->murderMystery.murderer = Card::FindAndRemoveCardOfTypeFromDeck(dealArray, Card::Type::Person);
	this->murderMystery.murderLocation = Card::FindAndRemoveCardOfTypeFromDeck(dealArray, Card::Type::Room);

	// Deal the remainder of the cards to all the players.
	int i = 0;
	while (dealArray.size() > 0)
	{
		std::shared_ptr<Card> card = dealArray.back();
		dealArray.pop_back();
		this->playerArray[i]->AddCard(card);
		i = (i + 1) % int(this->playerArray.size());
	}

	while (!this->winner.get())
		for (std::shared_ptr<Player>& player : this->playerArray)
			player->Participate(this);

	printf("%s won the game!\n", this->winner->GetName().c_str());
}

void CluedoGame::SolveTheMystery(const Accusation& accusation, std::shared_ptr<Player> player)
{
	if (player->IsDisqualified())
		return;

	// Note that I don't think it needs to be your turn when you do this.
	// You can choose to solve the mystery at any time.
	if (this->murderMystery == accusation)
		this->winner = player;
	else
	{
		player->SetDisqualfiied(true);
		printf("Player %s has become disqualfied!\n", player->GetName().c_str());
	}
}

const std::vector<std::shared_ptr<Card>>& CluedoGame::GetCardArray()
{
	return this->cardArray;
}

const std::vector<std::shared_ptr<Player>>& CluedoGame::GetPlayerArray()
{
	return this->playerArray;
}

bool CluedoGame::Accusation::operator==(const Accusation& accusation) const
{
	if (accusation.murderer != this->murderer)
		return false;

	if (accusation.murderWeapon != this->murderer)
		return false;

	if (accusation.murderLocation != this->murderLocation)
		return false;

	return true;
}