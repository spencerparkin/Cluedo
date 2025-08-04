#include "Card.h"

Card::Card(const std::string& name, Type type)
{
	this->name = name;
	this->type = type;
}

/*virtual*/ Card::~Card()
{
}

const std::string& Card::GetName() const
{
	return this->name;
}

Card::Type Card::GetType() const
{
	return this->type;
}

/*static*/ void Card::GenerateDeck(std::vector<std::shared_ptr<Card>>& cardArray)
{
	cardArray.clear();

	cardArray.push_back(std::make_shared<Card>("Candelstick", Card::Type::Weapon));
	cardArray.push_back(std::make_shared<Card>("Dagger", Card::Type::Weapon));
	cardArray.push_back(std::make_shared<Card>("Lead Pipe", Card::Type::Weapon));
	cardArray.push_back(std::make_shared<Card>("Revolver", Card::Type::Weapon));
	cardArray.push_back(std::make_shared<Card>("Rope", Card::Type::Weapon));
	cardArray.push_back(std::make_shared<Card>("Wrench", Card::Type::Weapon));

	cardArray.push_back(std::make_shared<Card>("Miss Scarlett", Card::Type::Person));
	cardArray.push_back(std::make_shared<Card>("Colonel Mustard", Card::Type::Person));
	cardArray.push_back(std::make_shared<Card>("Mrs. White", Card::Type::Person));
	cardArray.push_back(std::make_shared<Card>("Reverend Green", Card::Type::Person));
	cardArray.push_back(std::make_shared<Card>("Mrs. Peacock", Card::Type::Person));
	cardArray.push_back(std::make_shared<Card>("Professor Plum", Card::Type::Person));

	cardArray.push_back(std::make_shared<Card>("Kitchen", Card::Type::Room));
	cardArray.push_back(std::make_shared<Card>("Dining Room", Card::Type::Room));
	cardArray.push_back(std::make_shared<Card>("Lounge", Card::Type::Room));
	cardArray.push_back(std::make_shared<Card>("Ball Room", Card::Type::Room));
	cardArray.push_back(std::make_shared<Card>("Hall", Card::Type::Room));
	cardArray.push_back(std::make_shared<Card>("Conservatory", Card::Type::Room));
	cardArray.push_back(std::make_shared<Card>("Billiard Room", Card::Type::Room));
	cardArray.push_back(std::make_shared<Card>("Library", Card::Type::Room));
	cardArray.push_back(std::make_shared<Card>("Study", Card::Type::Room));
}

/*static*/ void Card::ShuffleCards(std::vector<std::shared_ptr<Card>>& cardArray)
{
	for (int i = 0; i < (int)cardArray.size() - 1; i++)
	{
		int j = RandomInteger(i, int(cardArray.size() - 1));
		if (i == j)
			continue;

		std::shared_ptr<Card> card = cardArray[i];
		cardArray[i] = cardArray[j];
		cardArray[j] = card;
	}
}

/*static*/ int Card::RandomInteger(int min, int max)
{
	int i = int(::round(double(min) + (double(std::rand()) / double(RAND_MAX)) * double(max - min)));
	if (i < min)
		i = min;
	if (i > max)
		i = max;
	return i;
}

/*static*/ std::shared_ptr<Card> Card::FindAndRemoveCardOfTypeFromDeck(std::vector<std::shared_ptr<Card>>& cardArray, Card::Type type)
{
	for (int i = 0; i < (int)cardArray.size(); i++)
	{
		std::shared_ptr<Card> card = cardArray[i];

		if (card->GetType() == type)
		{
			cardArray.erase(cardArray.begin() + i);
			return card;
		}
	}

	return std::shared_ptr<Card>();
}