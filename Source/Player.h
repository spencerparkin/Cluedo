#pragma once

#include "Card.h"

class CluedoGame;

class Player
{
public:
	Player(const std::string& name);
	virtual ~Player();

	virtual void Participate(CluedoGame* game) = 0;

	void AddCard(std::shared_ptr<Card> card);
	int GetNumCards() const;

	void SetDisqualfiied(bool isDisqualified);
	bool IsDisqualified() const;

	const std::string& GetName() const;

protected:
	std::vector<std::shared_ptr<Card>> cardArray;

private:
	bool isDisqualified;
	std::string name;
};