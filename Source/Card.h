#pragma once

#include <vector>
#include <map>

enum Room : int
{
	Kitchen,
	DiningRoom,
	Lounge,
	BallRoom,
	Hall,
	Conservatory,
	BilliardRoom,
	Library,
	Study
};

enum Weapon : int
{
	Candelstick,
	Dagger,
	LeadPipe,
	Reolver,
	Rope,
	Wrench
};

enum Character : int
{
	MissScarlett,
	ColonelMustard,
	MrsWhite,
	ReverendGreen,
	MrsPeacock,
	ProfessorPlum
};

struct Accusation
{
	Weapon weapon;
	Character character;
	Room room;

	bool operator==(const Accusation& accustaion) const;
};

struct Card
{
	enum Type
	{
		RoomType,
		WeaponType,
		CharacterType
	};

	Card();
	Card(int value, Type type);
	Card(const Card& card);

	bool operator==(const Card& card) const;
	bool operator<(const Card& card) const;

	union
	{
		Room room;
		Weapon weapon;
		Character character;
		int value;
	};

	Type type;

	static void GenerateDeck(std::vector<Card>& cardArray);
	static void ShuffleDeck(std::vector<Card>& cardArray);
	static bool FindAndRemoveCardOfType(std::vector<Card>& cardArray, Card::Type cardType, Card& removedCard);
	static int RandomInteger(int min, int max);
};

struct CardCompare
{
	bool operator()(const Card& cardA, const Card& cardB) const;
};

template<typename V>
class CardMap : public std::map<Card, V, CardCompare>
{
public:
};