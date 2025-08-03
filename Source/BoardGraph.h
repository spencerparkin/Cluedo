#pragma once

#include <memory>
#include <vector>
#include <unordered_set>
#include <functional>

#define CLUE_BOARD_WIDTH			24
#define CLUE_BOARD_HEIGHT			25

enum
{
	UU,			// Unused
	KN,			// Kitchen
	DR,			// Dining Room
	LG,			// Lounge
	BR,			// Ball Room
	CR,			// Center
	HL,			// Hall
	CY,			// Conservatory
	LR,			// Billiard Room
	LY,			// Library
	SY,			// Study
	HW			// Hall Way
};

enum Zone
{
	Unused,
	Kitchen,
	DiningRoom,
	Lounge,
	BallRoom,
	Center,
	Hall,
	Conservatory,
	BilliardRoom,
	Library,
	Study,
	Hallway
};
	
enum Character
{
	MissScarlett,
	ColonelMustard,
	MrsWhite,
	ReverendGreen,
	MrsPeacock,
	ProfessorPlum
};

enum Weapon
{
	Candelstick,
	Dagger,
	LeadPipe,
	Reolver,
	Rope,
	Wrench
};

/**
	* This class represents the playing field, its constraints, and where the
	* players are located on that field.
	*/
class BoardGraph
{
public:
	BoardGraph();
	virtual ~BoardGraph();

	void Regenerate();

	class Token
	{
		friend class BoardGraph;

	public:
		Token(Character character);
		virtual ~Token();

	private:
		Character character;
	};

	class Node
	{
		friend class BoardGraph;

	public:
		Node(Zone zone);
		virtual ~Node();

		bool IsRoom() const;
		Zone GetZone() const;
		const Token* GetOccupant() const;
		bool IsPathway(const Node* node) const;

	private:
		void AddPathway(Node* node);

		std::shared_ptr<Token> occupant;
		std::unordered_set<Node*> pathwayNodeSet;	// No need for weak pointer here.  Raw is fine.
		Zone zone;
	};

	void ForAllNodes(std::function<bool(const Node*)> callback) const;

private:
	std::vector<std::shared_ptr<Node>> nodeArray;
};