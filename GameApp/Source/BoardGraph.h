#pragma once

#include "Math/Vector2D.h"
#include "Math/Box2D.h"
#include "Card.h"
#include <memory>
#include <vector>
#include <unordered_set>
#include <functional>
#include <optional>
#include <mutex>

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
	bool IsGenerated() const;
	Box2D GetBoundingBox() const;

	class Node;

	class Token
	{
		friend class BoardGraph;

	public:
		Token(Character character);
		virtual ~Token();

		void SetNode(std::shared_ptr<Node> node);
		std::shared_ptr<Node> GetNode() const;

		const Vector2D& GetLocation() const;
		void GetColor(double& r, double& g, double& b) const;

		void Animate(double deltaTime);

	private:
		std::weak_ptr<Node> nodeWeakPtr;
		Character character;
		Vector2D location;
		double speed;
	};

	class Node
	{
		friend class BoardGraph;

	public:
		Node(std::optional<Room> room);
		virtual ~Node();

		bool IsRoom() const;
		const Vector2D& GetLocation() const;
		
		void GetAdjacencies(std::vector<const Node*>& adjacentNodeArray) const;
		bool IsPathway(const Node* node) const;

		std::optional<Room> GetRoom() const;

	private:
		void AddAdjacency(Node* node);
		void AddPathway(Node* node);

		std::unordered_set<Node*> adjacentNodeSet;
		std::unordered_set<Node*> pathwayNodeSet;
		std::optional<Room> room;

		Vector2D location;
	};

	void ForAllNodes(std::function<bool(const Node*)> callback) const;

	const std::vector<std::shared_ptr<Token>>& GetTokenArray() const;

	std::mutex& GetBoardGraphMutex();

private:
	std::mutex boardGraphMutex;
	std::vector<std::shared_ptr<Token>> tokenArray;
	std::vector<std::shared_ptr<Node>> nodeArray;
};