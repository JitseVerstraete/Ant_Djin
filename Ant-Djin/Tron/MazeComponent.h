#pragma once
#include <Component.h>
#include <vector>
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include "GameObject.h"
#include <iomanip>
#include <map>


enum class Direction
{
	North,
	South,
	East,
	West
};

class dae::GameObject;
class NodeComponent : public dae::Component
{
public:
	NodeComponent(dae::GameObject* pGo, int x, int y);

	void Update() override {}
	void FixedUpdate() override {}
	void Render() const override {}


	void AddNeighbor(NodeComponent* node, Direction dir);
	NodeComponent* GetNeighbor(Direction dir);




	friend std::ostream& operator<<(std::ostream& out, const NodeComponent* node)
	{
		std::cout << std::setprecision(2) << std::fixed;
		auto pos = node->GetGameObject()->GetTransform().GetWorldPosition();
		out << "Node:" << pos.x << ", " << pos.y << std::endl;
		if (node->m_NeighborNodes.find(Direction::West) != node->m_NeighborNodes.end()) out << "NODE LEFT\n";
		if (node->m_NeighborNodes.find(Direction::East) != node->m_NeighborNodes.end()) out << "NODE RIGHT\n";
		if (node->m_NeighborNodes.find(Direction::South) != node->m_NeighborNodes.end()) out << "NODE DOWN\n";
		if (node->m_NeighborNodes.find(Direction::North) != node->m_NeighborNodes.end()) out << "NODE UP\n";


		return out;
	}


private:
	std::map<Direction, NodeComponent*> m_NeighborNodes;

};


struct Connection
{

	enum class Alignment
	{
		Horizontal,
		Vertical
	};

	Connection(NodeComponent* first, NodeComponent* second, Alignment a) :first{ first }, second{ second }, alignment{ a } {}

	NodeComponent* first;
	NodeComponent* second;

	Alignment alignment;

	bool Equals(NodeComponent* node1, NodeComponent* node2)
	{
		if (node1 == first && node2 == second) return true;
		if (node2 == first && node1 == second) return true;
		return false;
	}
};

class MazeComponent final : public dae::Component
{
public:
	MazeComponent(dae::GameObject* pGo, std::string filePath);
	~MazeComponent();

	void Update() override;
	void FixedUpdate() override;
	void Render() const override;


	void AddNode(NodeComponent* pNode);
	void AddConnection(NodeComponent* first, NodeComponent* second);

	Connection* GetConnection(NodeComponent* node1, NodeComponent* node2);


	//get movement options given a current position

	const std::vector<NodeComponent*> GetAllNodes() const { return m_pNodes; }
	std::vector<NodeComponent*> GetPlayerSpawnPoints() const { return m_PlayerSpawns; }
	std::vector<NodeComponent*> GetEnemySpawnPoints() const { return m_EnemySpawns; }

	glm::ivec2 GetTeleporterPos() { return m_TeleporterPos; }


private:

	//general settings
	int m_MazeDimensions{};
	int m_PathWidth{ 15 };


	//nodes & connections
	std::vector<NodeComponent*> m_pNodes;
	std::vector<Connection*> m_Connections;

	glm::ivec2 m_TeleporterPos;

	std::vector<NodeComponent*> m_PlayerSpawns;
	std::vector<NodeComponent*> m_EnemySpawns;
	void ParseLevelFile(std::string path);


};



