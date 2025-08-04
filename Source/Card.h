#pragma once

#include <string>
#include <vector>
#include <memory>

class Card
{
public:
	enum Type
	{
		Weapon,
		Person,
		Room
	};

	Card(const std::string& name, Type type);
	virtual ~Card();

	const std::string& GetName() const;
	Type GetType() const;

	static void GenerateDeck(std::vector<std::shared_ptr<Card>>& cardArray);
	static void ShuffleCards(std::vector<std::shared_ptr<Card>>& cardArray);
	static int RandomInteger(int min, int max);
	static std::shared_ptr<Card> FindAndRemoveCardOfTypeFromDeck(std::vector<std::shared_ptr<Card>>& cardArray, Card::Type type);

private:
	std::string name;
	Type type;
};