#pragma once
#include <Component.h>
#include <vector>
#include <glm/glm.hpp>
#include <iostream>
#include <string>


struct Node
{
	Node(int x, int y) : pos{ x, y }
	{
	}

	glm::ivec2 pos;

	Node* pLeftNode = nullptr;
	Node* pRightNode = nullptr;
	Node* pUpNode = nullptr;
	Node* pDownNode = nullptr;

	friend std::ostream& operator<<(std::ostream& out, const Node& node)
	{
		out << "Node:" + std::to_string(node.pos.x) + ", " + std::to_string(node.pos.y) << std::endl;
		out << (node.pLeftNode ? "Node Left!\n" : "");
		out << (node.pRightNode ? "Node right!\n" : "");
		out << (node.pDownNode ? "Node down!\n" : "");
		out << (node.pUpNode ? "Node up!\n" : "");

		return out;
	}

};

struct Connection
{
	Connection(Node* first, Node* second) :first{ first }, second{ second } {}

	Node* first;
	Node* second;
};

class dae::GameObject;
class MazeComponent final : public dae::Component
{
public:
	MazeComponent(dae::GameObject* pGo, int size);
	~MazeComponent();

	void Update() override;
	void FixedUpdate() override;
	void Render() const override;


	void AddNode(Node* pNode);
	void AddConnection(Node* first, Node* second);


	//get movement options given a current position


private:

	const int m_MazeDimensions{};
	const int m_PathWidth{15};
	


	//nodes
	std::vector<Node*> m_pNodes;

	//connections (only for rendering purposes)
	std::vector<Connection> m_Connections;


};



