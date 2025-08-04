#include "Card.h"

bool Accusation::operator==(const Accusation& accusation) const
{
	if (this->room != accusation.room)
		return false;

	if (this->weapon != accusation.weapon)
		return false;

	if (this->character != accusation.character)
		return false;

	return true;
}

Card::Card()
{
	this->value = -1;
	this->type = Type::RoomType;
}

Card::Card(int value, Type type)
{
	this->value = value;
	this->type = type;
}

Card::Card(const Card& card)
{
	this->value = card.value;
	this->type = card.type;
}

bool Card::operator==(const Card& card) const
{
	return this->value == card.value && this->type == card.type;
}

bool Card::operator<(const Card& card) const
{
	if (this->type == card.type)
		return this->value < card.value;

	return this->type < card.type;
}

/*static*/ void Card::GenerateDeck(std::vector<Card>& cardArray)
{
	cardArray.clear();

	cardArray.push_back(Card({ Weapon::Candelstick, Type::WeaponType }));
	cardArray.push_back(Card({ Weapon::Dagger, Type::WeaponType }));
	cardArray.push_back(Card({ Weapon::LeadPipe, Type::WeaponType }));
	cardArray.push_back(Card({ Weapon::Reolver, Type::WeaponType }));
	cardArray.push_back(Card({ Weapon::Rope, Type::WeaponType }));
	cardArray.push_back(Card({ Weapon::Wrench, Type::WeaponType }));

	cardArray.push_back(Card({ Character::ColonelMustard, Type::CharacterType }));
	cardArray.push_back(Card({ Character::MissScarlett, Type::CharacterType }));
	cardArray.push_back(Card({ Character::MrsPeacock, Type::CharacterType }));
	cardArray.push_back(Card({ Character::MrsWhite, Type::CharacterType }));
	cardArray.push_back(Card({ Character::ProfessorPlum, Type::CharacterType }));
	cardArray.push_back(Card({ Character::ReverendGreen, Type::CharacterType }));

	cardArray.push_back(Card({ Room::BallRoom, Type::RoomType }));
	cardArray.push_back(Card({ Room::BilliardRoom, Type::RoomType }));
	cardArray.push_back(Card({ Room::Conservatory, Type::RoomType }));
	cardArray.push_back(Card({ Room::DiningRoom, Type::RoomType }));
	cardArray.push_back(Card({ Room::Hall, Type::RoomType }));
	cardArray.push_back(Card({ Room::Kitchen, Type::RoomType }));
	cardArray.push_back(Card({ Room::Library, Type::RoomType }));
	cardArray.push_back(Card({ Room::Lounge, Type::RoomType }));
	cardArray.push_back(Card({ Room::Study, Type::RoomType }));
}

/*static*/ void Card::ShuffleDeck(std::vector<Card>& cardArray)
{
	for (int i = 0; i < (int)cardArray.size() - 1; i++)
	{
		int j = RandomInteger(i, int(cardArray.size() - 1));
		if (i == j)
			continue;

		Card card = cardArray[i];
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

/*static*/ bool Card::FindAndRemoveCardOfType(std::vector<Card>& cardArray, Card::Type cardType, Card& removedCard)
{
	for (int i = 0; i < (int)cardArray.size(); i++)
	{
		const Card& card = cardArray[i];

		if (card.type == cardType)
		{
			removedCard = card;
			cardArray.erase(cardArray.begin() + i);
			return true;
		}
	}

	return true;
}

bool CardCompare::operator()(const Card& cardA, const Card& cardB) const
{
	return cardA < cardB;
}