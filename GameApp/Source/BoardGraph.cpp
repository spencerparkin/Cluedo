#include "BoardGraph.h"
#include <assert.h>

#define CLUE_BOARD_WIDTH			24
#define CLUE_BOARD_HEIGHT			25

#define KN			Room::Kitchen
#define DR			Room::DiningRoom
#define LG			Room::Lounge
#define BR			Room::BallRoom
#define HL			Room::Hall
#define CY			Room::Conservatory
#define LR			Room::BilliardRoom
#define LY			Room::Library
#define SY			Room::Study
#define HW			-1
#define CR			-2
#define UU			-3

static int boardMatrix[CLUE_BOARD_HEIGHT][CLUE_BOARD_WIDTH] =
{
	{UU, UU, UU, UU, UU, UU, UU, UU, UU, HW, UU, UU, UU, UU, HW, UU, UU, UU, UU, UU, UU, UU, UU, UU},
	{KN, KN, KN, KN, KN, KN, UU, HW, HW, HW, BR, BR, BR, BR, HW, HW, HW, UU, CY, CY, CY, CY, CY, CY},
	{KN, KN, KN, KN, KN, KN, HW, HW, BR, BR, BR, BR, BR, BR, BR, BR, HW, HW, CY, CY, CY, CY, CY, CY},
	{KN, KN, KN, KN, KN, KN, HW, HW, BR, BR, BR, BR, BR, BR, BR, BR, HW, HW, CY, CY, CY, CY, CY, CY},
	{KN, KN, KN, KN, KN, KN, HW, HW, BR, BR, BR, BR, BR, BR, BR, BR, HW, HW, CY, CY, CY, CY, CY, CY},
	{KN, KN, KN, KN, KN, KN, HW, HW, BR, BR, BR, BR, BR, BR, BR, BR, HW, HW, HW, CY, CY, CY, CY, UU},
	{UU, KN, KN, KN, KN, KN, HW, HW, BR, BR, BR, BR, BR, BR, BR, BR, HW, HW, HW, HW, HW, HW, HW, HW},
	{HW, HW, HW, HW, HW, HW, HW, HW, BR, BR, BR, BR, BR, BR, BR, BR, HW, HW, HW, HW, HW, HW, HW, UU},
	{UU, HW, HW, HW, HW, HW, HW, HW, HW, HW, HW, HW, HW, HW, HW, HW, HW, HW, LR, LR, LR, LR, LR, LR},
	{DR, DR, DR, DR, DR, HW, HW, HW, HW, HW, HW, HW, HW, HW, HW, HW, HW, HW, LR, LR, LR, LR, LR, LR},
	{DR, DR, DR, DR, DR, DR, DR, DR, HW, HW, CR, CR, CR, CR, CR, HW, HW, HW, LR, LR, LR, LR, LR, LR},
	{DR, DR, DR, DR, DR, DR, DR, DR, HW, HW, CR, CR, CR, CR, CR, HW, HW, HW, LR, LR, LR, LR, LR, LR},
	{DR, DR, DR, DR, DR, DR, DR, DR, HW, HW, CR, CR, CR, CR, CR, HW, HW, HW, LR, LR, LR, LR, LR, LR},
	{DR, DR, DR, DR, DR, DR, DR, DR, HW, HW, CR, CR, CR, CR, CR, HW, HW, HW, HW, HW, HW, HW, HW, UU},
	{DR, DR, DR, DR, DR, DR, DR, DR, HW, HW, CR, CR, CR, CR, CR, HW, HW, HW, LY, LY, LY, LY, LY, UU},
	{DR, DR, DR, DR, DR, DR, DR, DR, HW, HW, CR, CR, CR, CR, CR, HW, HW, LY, LY, LY, LY, LY, LY, LY},
	{UU, HW, HW, HW, HW, HW, HW, HW, HW, HW, CR, CR, CR, CR, CR, HW, HW, LY, LY, LY, LY, LY, LY, LY},
	{HW, HW, HW, HW, HW, HW, HW, HW, HW, HW, HW, HW, HW, HW, HW, HW, HW, LY, LY, LY, LY, LY, LY, LY},
	{UU, HW, HW, HW, HW, HW, HW, HW, HW, HL, HL, HL, HL, HL, HL, HW, HW, HW, LY, LY, LY, LY, LY, UU},
	{LG, LG, LG, LG, LG, LG, LG, HW, HW, HL, HL, HL, HL, HL, HL, HW, HW, HW, HW, HW, HW, HW, HW, HW},
	{LG, LG, LG, LG, LG, LG, LG, HW, HW, HL, HL, HL, HL, HL, HL, HW, HW, HW, HW, HW, HW, HW, HW, UU},
	{LG, LG, LG, LG, LG, LG, LG, HW, HW, HL, HL, HL, HL, HL, HL, HW, HW, SY, SY, SY, SY, SY, SY, SY},
	{LG, LG, LG, LG, LG, LG, LG, HW, HW, HL, HL, HL, HL, HL, HL, HW, HW, SY, SY, SY, SY, SY, SY, SY},
	{LG, LG, LG, LG, LG, LG, LG, HW, HW, HL, HL, HL, HL, HL, HL, HW, HW, SY, SY, SY, SY, SY, SY, SY},
	{LG, LG, LG, LG, LG, LG, UU, HW, UU, UU, UU, UU, UU, UU, UU, UU, HW, UU, SY, SY, SY, SY, SY, SY}
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

bool BoardGraph::IsGenerated() const
{
	return this->nodeArray.size() > 0 && this->tokenArray.size() > 0;
}

void BoardGraph::Regenerate()
{
	this->tokenArray.clear();
	this->nodeArray.clear();

	std::shared_ptr<Node> nodeMatrix[CLUE_BOARD_HEIGHT][CLUE_BOARD_WIDTH];

	for (int i = 0; i < CLUE_BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < CLUE_BOARD_WIDTH; j++)
		{
			std::optional<Room> room;
			int roomCode = boardMatrix[i][j];
			if (roomCode >= 0)
				room = Room(roomCode);

			std::shared_ptr<Node> node = std::make_shared<Node>(room);

			node->location.x = double(j);
			node->location.y = double(CLUE_BOARD_HEIGHT - 1 - i);

			nodeMatrix[i][j] = node;
			this->nodeArray.push_back(node);
		}
	}

	for (int i = 0; i < CLUE_BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < CLUE_BOARD_WIDTH; j++)
		{
			std::shared_ptr<Node> node = nodeMatrix[i][j];

			if (i - 1 >= 0)
				node->AddAdjacency(nodeMatrix[i - 1][j].get());

			if (i + 1 < CLUE_BOARD_HEIGHT)
				node->AddAdjacency(nodeMatrix[i + 1][j].get());

			if (j - 1 >= 0)
				node->AddAdjacency(nodeMatrix[i][j - 1].get());

			if (j + 1 < CLUE_BOARD_WIDTH)
				node->AddAdjacency(nodeMatrix[i][j + 1].get());
		}
	}

	for (int i = 0; i < CLUE_BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < CLUE_BOARD_WIDTH; j++)
		{
			std::shared_ptr<Node> node = nodeMatrix[i][j];

			if (i - 1 >= 0 && nodeMatrix[i - 1][j]->room == node->room)
				node->AddPathway(nodeMatrix[i - 1][j].get());

			if (i + 1 < CLUE_BOARD_HEIGHT && nodeMatrix[i + 1][j]->room == node->room)
				node->AddPathway(nodeMatrix[i + 1][j].get());

			if (j - 1 >= 0 && nodeMatrix[i][j - 1]->room == node->room)
				node->AddPathway(nodeMatrix[i][j - 1].get());

			if (j + 1 < CLUE_BOARD_WIDTH && nodeMatrix[i][j + 1]->room == node->room)
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

	// TODO: What about the secret passages?

	for (const StartLocation& startLocation : startLocationArray)
	{
		Node* node = nodeMatrix[startLocation.i][startLocation.j].get();

		assert(!node->IsRoom());

		std::shared_ptr<Token> token = std::make_shared<Token>(startLocation.character);
		token->location = node->location;
		this->tokenArray.push_back(token);
	}
}

Box2D BoardGraph::GetBoundingBox() const
{
	Box2D boundingBox;
	for (const std::shared_ptr<Node>& node : this->nodeArray)
		boundingBox.ExpandToIncludePoint(node->location);

	return boundingBox;
}

void BoardGraph::ForAllNodes(std::function<bool(const Node*)> callback) const
{
	for (const std::shared_ptr<Node>& node : this->nodeArray)
		if (!callback(node.get()))
			break;
}

const std::vector<std::shared_ptr<BoardGraph::Token>>& BoardGraph::GetTokenArray() const
{
	return this->tokenArray;
}

std::mutex& BoardGraph::GetBoardGraphMutex()
{
	return this->boardGraphMutex;
}

//-------------------------------------- BoardGraph::Node --------------------------------------

BoardGraph::Node::Node(std::optional<Room> room)
{
	this->room = room;
}

/*virtual*/ BoardGraph::Node::~Node()
{
}

bool BoardGraph::Node::IsRoom() const
{
	return this->room.has_value();
}

std::optional<Room> BoardGraph::Node::GetRoom() const
{
	return this->room;
}

const Vector2D& BoardGraph::Node::GetLocation() const
{
	return this->location;
}

void BoardGraph::Node::AddAdjacency(Node* node)
{
	this->adjacentNodeSet.insert(node);
	node->adjacentNodeSet.insert(this);
}

void BoardGraph::Node::AddPathway(Node* node)
{
	this->pathwayNodeSet.insert(node);
	node->pathwayNodeSet.insert(this);
}

void BoardGraph::Node::GetAdjacencies(std::vector<const Node*>& adjacentNodeArray) const
{
	adjacentNodeArray.clear();
	for (Node* node : this->adjacentNodeSet)
		adjacentNodeArray.push_back(node);
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
	this->speed = 1.0;
}

/*virtual*/ BoardGraph::Token::~Token()
{
}

void BoardGraph::Token::SetNode(std::shared_ptr<Node> node)
{
	this->nodeWeakPtr = node;
}

std::shared_ptr<BoardGraph::Node> BoardGraph::Token::GetNode() const
{
	return this->nodeWeakPtr.lock();
}

void BoardGraph::Token::Animate(double deltaTime)
{
	std::shared_ptr<Node> node = this->nodeWeakPtr.lock();
	if (!node.get())
		return;

	Vector2D vector = node->GetLocation() - this->location;
	double length = vector.Length();
	if (length == 0.0)
		return;

	Vector2D delta = (vector / length) * this->speed * deltaTime;
	this->location += delta;
}

const Vector2D& BoardGraph::Token::GetLocation() const
{
	return this->location;
}

void BoardGraph::Token::GetColor(double& r, double& g, double& b) const
{
	r = 0.0;
	g = 0.0;
	b = 0.0;

	switch (this->character)
	{
		case Character::MissScarlett:
		{
			r = 1.0;
			g = 0.0;
			b = 0.0;
			break;
		}
		case Character::ColonelMustard:
		{
			r = 0.0;
			g = 1.0;
			b = 1.0;
			break;
		}
		case Character::MrsWhite:
		{
			r = 1.0;
			g = 1.0;
			b = 1.0;
			break;
		}
		case Character::ReverendGreen:
		{
			r = 0.0;
			g = 1.0;
			b = 0.0;
			break;
		}
		case Character::MrsPeacock:
		{
			r = 0.0;
			g = 0.0;
			b = 1.0;
			break;
		}
		case Character::ProfessorPlum:
		{
			r = 1.0;
			g = 1.0;
			b = 0.0;
			break;
		}
	}
}