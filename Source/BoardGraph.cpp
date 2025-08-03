#include "BoardGraph.h"
#include <assert.h>

static int boardMatrix[CLUE_BOARD_HEIGHT][CLUE_BOARD_WIDTH] =
{
	{Unused, Unused, Unused, Unused, Unused, Unused, Unused, Unused, Unused, Hallway, Unused, Unused, Unused, Unused, Hallway, Unused, Unused, Unused, Unused, Unused, Unused, Unused, Unused, Unused},
	{Kitchen, Kitchen, Kitchen, Kitchen, Kitchen, Kitchen, Unused, Hallway, Hallway, Hallway, BallRoom, BallRoom, BallRoom, BallRoom, Hallway, Hallway, Hallway, Unused, Conservatory, Conservatory, Conservatory, Conservatory, Conservatory, Conservatory},
	{Kitchen, Kitchen, Kitchen, Kitchen, Kitchen, Kitchen, Hallway, Hallway, BallRoom, BallRoom, BallRoom, BallRoom, BallRoom, BallRoom, BallRoom, BallRoom, Hallway, Hallway, Conservatory, Conservatory, Conservatory, Conservatory, Conservatory, Conservatory},
	{Kitchen, Kitchen, Kitchen, Kitchen, Kitchen, Kitchen, Hallway, Hallway, BallRoom, BallRoom, BallRoom, BallRoom, BallRoom, BallRoom, BallRoom, BallRoom, Hallway, Hallway, Conservatory, Conservatory, Conservatory, Conservatory, Conservatory, Conservatory},
	{Kitchen, Kitchen, Kitchen, Kitchen, Kitchen, Kitchen, Hallway, Hallway, BallRoom, BallRoom, BallRoom, BallRoom, BallRoom, BallRoom, BallRoom, BallRoom, Hallway, Hallway, Conservatory, Conservatory, Conservatory, Conservatory, Conservatory, Conservatory},
	{Kitchen, Kitchen, Kitchen, Kitchen, Kitchen, Kitchen, Hallway, Hallway, BallRoom, BallRoom, BallRoom, BallRoom, BallRoom, BallRoom, BallRoom, BallRoom, Hallway, Hallway, Hallway, Conservatory, Conservatory, Conservatory, Conservatory, Unused},
	{Unused, Kitchen, Kitchen, Kitchen, Kitchen, Kitchen, Hallway, Hallway, BallRoom, BallRoom, BallRoom, BallRoom, BallRoom, BallRoom, BallRoom, BallRoom, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway},
	{Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, BallRoom, BallRoom, BallRoom, BallRoom, BallRoom, BallRoom, BallRoom, BallRoom, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Unused},
	{Unused, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, BilliardRoom, BilliardRoom, BilliardRoom, BilliardRoom, BilliardRoom, BilliardRoom},
	{DiningRoom, DiningRoom, DiningRoom, DiningRoom, DiningRoom, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, BilliardRoom, BilliardRoom, BilliardRoom, BilliardRoom, BilliardRoom, BilliardRoom},
	{DiningRoom, DiningRoom, DiningRoom, DiningRoom, DiningRoom, DiningRoom, DiningRoom, DiningRoom, Hallway, Hallway, Center, Center, Center, Center, Center, Hallway, Hallway, Hallway, BilliardRoom, BilliardRoom, BilliardRoom, BilliardRoom, BilliardRoom, BilliardRoom},
	{DiningRoom, DiningRoom, DiningRoom, DiningRoom, DiningRoom, DiningRoom, DiningRoom, DiningRoom, Hallway, Hallway, Center, Center, Center, Center, Center, Hallway, Hallway, Hallway, BilliardRoom, BilliardRoom, BilliardRoom, BilliardRoom, BilliardRoom, BilliardRoom},
	{DiningRoom, DiningRoom, DiningRoom, DiningRoom, DiningRoom, DiningRoom, DiningRoom, DiningRoom, Hallway, Hallway, Center, Center, Center, Center, Center, Hallway, Hallway, Hallway, BilliardRoom, BilliardRoom, BilliardRoom, BilliardRoom, BilliardRoom, BilliardRoom},
	{DiningRoom, DiningRoom, DiningRoom, DiningRoom, DiningRoom, DiningRoom, DiningRoom, DiningRoom, Hallway, Hallway, Center, Center, Center, Center, Center, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Unused},
	{DiningRoom, DiningRoom, DiningRoom, DiningRoom, DiningRoom, DiningRoom, DiningRoom, DiningRoom, Hallway, Hallway, Center, Center, Center, Center, Center, Hallway, Hallway, Hallway, Library, Library, Library, Library, Library, Unused},
	{DiningRoom, DiningRoom, DiningRoom, DiningRoom, DiningRoom, DiningRoom, DiningRoom, DiningRoom, Hallway, Hallway, Center, Center, Center, Center, Center, Hallway, Hallway, Library, Library, Library, Library, Library, Library, Library},
	{Unused, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Center, Center, Center, Center, Center, Hallway, Hallway, Library, Library, Library, Library, Library, Library, Library},
	{Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Library, Library, Library, Library, Library, Library, Library},
	{Unused, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hall, Hall, Hall, Hall, Hall, Hall, Hallway, Hallway, Hallway, Library, Library, Library, Library, Library, Unused},
	{Lounge, Lounge, Lounge, Lounge, Lounge, Lounge, Lounge, Hallway, Hallway, Hall, Hall, Hall, Hall, Hall, Hall, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway},
	{Lounge, Lounge, Lounge, Lounge, Lounge, Lounge, Lounge, Hallway, Hallway, Hall, Hall, Hall, Hall, Hall, Hall, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Hallway, Unused},
	{Lounge, Lounge, Lounge, Lounge, Lounge, Lounge, Lounge, Hallway, Hallway, Hall, Hall, Hall, Hall, Hall, Hall, Hallway, Hallway, Study, Study, Study, Study, Study, Study, Study},
	{Lounge, Lounge, Lounge, Lounge, Lounge, Lounge, Lounge, Hallway, Hallway, Hall, Hall, Hall, Hall, Hall, Hall, Hallway, Hallway, Study, Study, Study, Study, Study, Study, Study},
	{Lounge, Lounge, Lounge, Lounge, Lounge, Lounge, Lounge, Hallway, Hallway, Hall, Hall, Hall, Hall, Hall, Hall, Hallway, Hallway, Study, Study, Study, Study, Study, Study, Study},
	{Lounge, Lounge, Lounge, Lounge, Lounge, Lounge, Unused, Hallway, Unused, Unused, Unused, Unused, Unused, Unused, Unused, Unused, Hallway, Unused, Study, Study, Study, Study, Study, Study}
};

struct Doorway
{
	int i, j;
	int di, dj;
};

static Doorway doorwayArray[] = {
	{7, 4, -1, 0},
	{5, 7, 0, 1},
	{5, 16, 0, -1},
	{5, 18, -1, 0},
	{8, 9, -1, 0},
	{8, 14, -1, 0},
	{12, 8, 0, -1},
	{9, 17, 0, 1},
	{13, 20, 1, 0},
	{13, 22, -1, 0},
	{16, 6, -1, 0},
	{16, 16, 0, 1},
	{17, 11, 1, 0},
	{17, 12, 1, 0},
	{18, 6, 1, 0},
	{20, 15, 0, -1},
	{20, 17, 1, 0}
};

struct StartLocation
{
	int i, j;
	Character character;
};

static StartLocation startLocationArray[] = {
	{0, 9, Character::MrsWhite},
	{0, 14, Character::ReverendGreen},
	{6, 23, Character::MrsPeacock},
	{17, 0, Character::ColonelMustard},
	{24, 7, Character::MissScarlett},
	{19, 23, Character::ProfessorPlum}
};

//-------------------------------------- BoardGraph --------------------------------------

BoardGraph::BoardGraph()
{
}

/*virtual*/ BoardGraph::~BoardGraph()
{
}

void BoardGraph::Regenerate()
{
	this->nodeArray.clear();

	std::shared_ptr<Node> nodeMatrix[CLUE_BOARD_HEIGHT][CLUE_BOARD_WIDTH];

	for (int i = 0; i < CLUE_BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < CLUE_BOARD_WIDTH; j++)
		{
			std::shared_ptr<Node> node = std::make_shared<Node>((Zone)boardMatrix[i][j]);

			nodeMatrix[i][j] = node;
			this->nodeArray.push_back(node);
		}
	}

	for (int i = 0; i < CLUE_BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < CLUE_BOARD_WIDTH; j++)
		{
			std::shared_ptr<Node> node = nodeMatrix[i][j];

			if (i - 1 >= 0 && nodeMatrix[i - 1][j]->zone == node->zone)
				node->AddPathway(nodeMatrix[i - 1][j].get());

			if (i + 1 < CLUE_BOARD_HEIGHT && nodeMatrix[i + 1][j]->zone == node->zone)
				node->AddPathway(nodeMatrix[i + 1][j].get());

			if (j - 1 >= 0 && nodeMatrix[i][j - 1]->zone == node->zone)
				node->AddPathway(nodeMatrix[i][j - 1].get());

			if (j + 1 < CLUE_BOARD_WIDTH && nodeMatrix[i][j + 1]->zone == node->zone)
				node->AddPathway(nodeMatrix[i][j + 1].get());
		}
	}

	for (const Doorway& doorway : doorwayArray)
	{
		std::shared_ptr<Node> nodeA = nodeMatrix[doorway.i][doorway.j];
		std::shared_ptr<Node> nodeB = nodeMatrix[doorway.i + doorway.di][doorway.j + doorway.dj];

		assert(!nodeA->IsRoom() && nodeB->IsRoom());

		nodeA->AddPathway(nodeB.get());
	}

	for (const StartLocation& startLocation : startLocationArray)
	{
		Node* node = nodeMatrix[startLocation.i][startLocation.j].get();

		assert(!node->IsRoom());

		// Note that while there can be at most one occupant per node, you can
		// still get multiple occupants per room, because 1) each room has enough
		// nodes for all players, and 2) there is no cost to move from one room
		// location to another in terms of the dice roll.
		node->occupant = std::make_shared<Token>(startLocation.character);
	}
}

void BoardGraph::ForAllNodes(std::function<bool(const Node*)> callback) const
{
	for (const std::shared_ptr<Node>& node : this->nodeArray)
		if (!callback(node.get()))
			break;
}

//-------------------------------------- BoardGraph::Node --------------------------------------

BoardGraph::Node::Node(Zone zone)
{
	this->zone = zone;
}

/*virtual*/ BoardGraph::Node::~Node()
{
}

bool BoardGraph::Node::IsRoom() const
{
	switch (this->zone)
	{
	case Zone::Hallway:
	case Zone::Unused:
		return false;
	}

	return true;
}

Zone BoardGraph::Node::GetZone() const
{
	return this->zone;
}

const BoardGraph::Token* BoardGraph::Node::GetOccupant() const
{
	return this->occupant.get();
}

void BoardGraph::Node::AddPathway(Node* node)
{
	this->pathwayNodeSet.insert(node);
	node->pathwayNodeSet.insert(this);
}

bool BoardGraph::Node::IsPathway(const Node* node) const
{
	auto iter = this->pathwayNodeSet.find(const_cast<Node*>(node));
	return iter != this->pathwayNodeSet.end();
}

//-------------------------------------- BoardGraph::Token --------------------------------------

BoardGraph::Token::Token(Character character)
{
	this->character = character;
}

/*virtual*/ BoardGraph::Token::~Token()
{
}