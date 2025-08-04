#pragma once

#include "Card.h"
#include <memory>
#include <vector>
#include <string>

class Player;

class CluedoGame
{
public:
	CluedoGame();
	virtual ~CluedoGame();

	bool AddPlayer(std::shared_ptr<Player> player);
	void Play();

	struct Accusation
	{
		std::shared_ptr<Card> murderer;
		std::shared_ptr<Card> murderWeapon;
		std::shared_ptr<Card> murderLocation;

		bool operator==(const Accusation& accusation) const;
	};

	void SolveTheMystery(const Accusation& accusation, std::shared_ptr<Player> player);
	const std::vector<std::shared_ptr<Card>>& GetCardArray();
	const std::vector<std::shared_ptr<Player>>& GetPlayerArray();
	// TODO: Add API for basic game-play mechanics.

private:

	Accusation murderMystery;
	// TODO: Keep track of whose turn it is here.
	// TODO: If an accusation is being made, track here who it is that is to disprove it or pass.
	std::shared_ptr<Player> winner;
	std::vector<std::shared_ptr<Card>> cardArray;
	std::vector<std::shared_ptr<Player>> playerArray;
};