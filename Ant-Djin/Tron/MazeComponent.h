#pragma once
#include <Component.h>
#include <vector>
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include "GameObject.h"



class dae::GameObject;
class NodeComponent : public dae::Component
{
public:
	NodeComponent(dae::GameObject* pGo, int x, int y);

	NodeComponent* pLeftNode = nullptr;
	NodeComponent* pRightNode = nullptr;
	NodeComponent* pUpNode = nullptr;
	NodeComponent* pDownNode = nullptr;


	void Update() override {}
	void FixedUpdate() override {}
	void Render() const override {}
	

	/*
	friend std::ostream& operator<<(std::ostream& out, const NodeComponent* node)
	{	
		
		out << "Node:" + std::to_string(node.pos.x) + ", " + std::to_string(node.pos.y) << std::endl;
		out << (node.pLeftNode ? "Node Left!\n" : "");
		out << (node.pRightNode ? "Node right!\n" : "");
		out << (node.pDownNode ? "Node down!\n" : "");
		out << (node.pUpNode ? "Node up!\n" : "");
	

		return out;
	}
	*/

};

struct Connection
{
	Connection(NodeComponent* first, NodeComponent* second) :first{ first }, second{ second } {}

	NodeComponent* first;
	NodeComponent* second;
};

class MazeComponent final : public dae::Component
{
public:
	MazeComponent(dae::GameObject* pGo, int size);
	~MazeComponent();

	void Update() override;
	void FixedUpdate() override;
	void Render() const override;


	void AddNode(NodeComponent* pNode);
	void AddConnection(NodeComponent* first, NodeComponent* second);


	//get movement options given a current position

	NodeComponent* GetSpawnPoint() const { return m_pNodes[0]; }


private:

	const int m_MazeDimensions{};
	const int m_PathWidth{15};
	


	//nodes
	std::vector<NodeComponent*> m_pNodes;

	//connections (only for rendering purposes)
	std::vector<Connection> m_Connections;


};



