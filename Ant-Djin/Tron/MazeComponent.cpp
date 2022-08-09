#include "MazeComponent.h"
#include "Renderer.h"
#include <iostream>
#include "GameObject.h"

using namespace dae;

MazeComponent::MazeComponent(GameObject* pGo, int size) : Component(pGo), m_MazeDimensions{ size }
{
	//initialize everything to do with the maze (load in from file perhaps)
	Node* testNode1 = new Node(20, 100);
	Node* testNode2 = new Node(200, 100);
	Node* testNode3 = new Node(200, 180);

	AddNode(testNode1);
	AddNode(testNode2);
	AddNode(testNode3);

	AddConnection(testNode1, testNode2);
	AddConnection(testNode2, testNode3);

	for (Node* pNode : m_pNodes)
	{
		std::cout << (*pNode) << std::endl;
	}
}

MazeComponent::~MazeComponent()
{

}

void MazeComponent::Update()
{
}

void MazeComponent::FixedUpdate()
{
}

void MazeComponent::Render() const
{
	//render background
	glm::ivec2 pos = GetGameObject()->GetTransform().GetWorldPosition();
	Renderer::GetInstance().DrawRectangle({ pos.x, pos.y }, { m_MazeDimensions, m_MazeDimensions }, { 0, 170, 0, 255 });

	//render pathways
	for (Connection con : m_Connections)
	{
		int rectWidth{ m_PathWidth * 2 + abs(con.first->pos.x - con.second->pos.x) };
		int rechtHeight{ m_PathWidth * 2 + abs(con.first->pos.y - con.second->pos.y) };
		Renderer::GetInstance().DrawRectangle({ con.first->pos.x - m_PathWidth + pos.x, con.first->pos.y - m_PathWidth + pos.y }, {rectWidth, rechtHeight}, { 0, 0, 0, 255 });
	}

	//render nodes


	//render connection lines
	for (Connection con : m_Connections)
	{
		Renderer::GetInstance().DrawLine(con.first->pos + pos, con.second->pos + pos, { 255, 0, 0, 255 });
	}
}

void MazeComponent::AddNode(Node* pNode)
{
	m_pNodes.emplace_back(pNode);
}

void MazeComponent::AddConnection(Node* first, Node* second)
{

	bool xSame{ first->pos.x == second->pos.x };
	bool ySame{ first->pos.y == second->pos.y };

	//check if the nodes are aligned horizontally or vertically
	if (!xSame && !ySame)
	{
		std::cout << "Connection not possible, the nodes are not alligned horizontally or vertically\n";
		return;
	}

	//check if the nodes have a different pos
	if (first->pos == second->pos)
	{
		std::cout << "Connection not possible, nodes have the same position";
		return;
	}

	//add the node to the maze
	m_Connections.emplace_back(Connection(first, second));



	if (xSame)
	{
		if (first->pos.y < second->pos.y)
		{
			first->pDownNode = second;
			second->pUpNode = first;
		}
		else
		{
			first->pUpNode = second;
			second->pDownNode = first;
		}
	}
	else if (ySame)
	{
		if (first->pos.x < second->pos.x)
		{
			first->pRightNode = second;
			second->pLeftNode = first;
		}
		else
		{
			first->pLeftNode = second;
			second->pRightNode = first;
		}

	}



}
