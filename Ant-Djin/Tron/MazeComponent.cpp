#include "MazeComponent.h"
#include "Renderer.h"
#include <iostream>
#include "GameObject.h"
#include "SceneManager.h"
#include "GameScene.h"
#include <algorithm>


using namespace dae;




NodeComponent::NodeComponent(GameObject* pGo, int x, int y)
	:Component(pGo)
{
	GetGameObject()->GetTransform().SetLocalPosition({ x, y, 0 });
}

void NodeComponent::AddNeighbor(NodeComponent* node, Direction dir)
{
	if (m_NeighborNodes.find(dir) == m_NeighborNodes.end())
	{
		std::cout << "trying to add a neighbor node to a node that already has a neighbor in the specified direction\n";
		return;
	}

	m_NeighborNodes.insert({dir, node});

}

NodeComponent* NodeComponent::GetNeighbor(Direction dir)
{
	auto it = m_NeighborNodes.find(dir);
	if (it != m_NeighborNodes.end()) return it->second;
	return nullptr;
}

//maze stuff
MazeComponent::MazeComponent(GameObject* pGo, int size) : Component(pGo), m_MazeDimensions{ size }
{
	//initialize everything to do with the maze (load in from file perhaps)
	GameObject* go = SceneManager::GetInstance().GetActiveScene()->AddGameObject();
	NodeComponent* testNode1 = go->AddComponent(new NodeComponent(go, 70, 100));
	go->GetTransform().SetParent(&GetGameObject()->GetTransform());

	go = SceneManager::GetInstance().GetActiveScene()->AddGameObject();
	NodeComponent* testNode2 = go->AddComponent(new NodeComponent(go, 300, 100));
	go->GetTransform().SetParent(&GetGameObject()->GetTransform());

	go = SceneManager::GetInstance().GetActiveScene()->AddGameObject();
	NodeComponent* testNode3 = go->AddComponent(new NodeComponent(go, 300, 250));
	go->GetTransform().SetParent(&GetGameObject()->GetTransform());

	go = SceneManager::GetInstance().GetActiveScene()->AddGameObject();
	NodeComponent* testNode4 = go->AddComponent(new NodeComponent(go, 500, 100));
	go->GetTransform().SetParent(&GetGameObject()->GetTransform());

	AddNode(testNode1);
	AddNode(testNode2);
	AddNode(testNode3);
	AddNode(testNode4);

	AddConnection(testNode1, testNode2);
	AddConnection(testNode2, testNode3);
	AddConnection(testNode2, testNode4);

	for (NodeComponent* pNode : m_pNodes)
	{
		std::cout << pNode << std::endl;
	}

}

MazeComponent::~MazeComponent()
{
	for (Connection* con : m_Connections)
	{
		delete con;
	}
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
	Renderer::GetInstance().DrawRectangle({ GetGameObject()->GetTransform().GetWorldPosition().x,GetGameObject()->GetTransform().GetWorldPosition().y }, { m_MazeDimensions, m_MazeDimensions }, { 0, 170, 0, 255 });


	//render pathways
	for (Connection* con : m_Connections)
	{
		glm::ivec3 firstPos = con->first->GetGameObject()->GetTransform().GetWorldPosition();
		glm::ivec3 secondPos = con->second->GetGameObject()->GetTransform().GetWorldPosition();

		int rectWidth{ m_PathWidth * 2 + abs(firstPos.x - secondPos.x) };
		int rechtHeight{ m_PathWidth * 2 + abs(firstPos.y - secondPos.y) };
		Renderer::GetInstance().DrawRectangle({ firstPos.x - m_PathWidth , firstPos.y - m_PathWidth }, { rectWidth, rechtHeight }, { 0, 0, 0, 255 });
	}

	//render nodes


	//render connection lines
	for (Connection* con : m_Connections)
	{
		Renderer::GetInstance().DrawLine(glm::ivec2(con->first->GetGameObject()->GetTransform().GetWorldPosition()),
			glm::ivec2(con->second->GetGameObject()->GetTransform().GetWorldPosition()),
			{ 255, 0, 0, 255 });
	}
}

void MazeComponent::AddNode(NodeComponent* pNode)
{
	m_pNodes.emplace_back(pNode);
}

void MazeComponent::AddConnection(NodeComponent* node1, NodeComponent* node2)
{
	glm::ivec3 pos1 = node1->GetGameObject()->GetTransform().GetLocalPosition();
	glm::ivec3 pos2 = node2->GetGameObject()->GetTransform().GetLocalPosition();
	bool xSame{ pos1.x == pos2.x };
	bool ySame{ pos1.y == pos2.y };

	//check if the nodes are aligned horizontally or vertically
	if (!xSame && !ySame)
	{
		std::cout << "Connection not possible, the nodes are not alligned horizontally or vertically\n";
		return;
	}

	//check if the nodes have a different pos
	if (pos1 == pos2)
	{
		std::cout << "Connection not possible, nodes have the same position";
		return;
	}

	NodeComponent* firstNode{}; //first node is the node on the left/on the top of the connection
	NodeComponent* secondNode{};
	Connection::Alignment alignment{};

	if (xSame)
	{
		if (pos1.y < pos2.y)
		{
			firstNode = node1;
			secondNode = node2;
		}
		else
		{
			firstNode = node2;
			secondNode = node1;
		}

		firstNode->AddNeighbor(secondNode, Direction::South);
		secondNode->AddNeighbor(firstNode, Direction::North);
		alignment = Connection::Alignment::Horizontal;
	}
	else if (ySame)
	{
		if (pos1.x < pos2.x)
		{
			firstNode = node1;
			secondNode = node2;
		}
		else
		{
			firstNode = node2;
			secondNode = node1;
		}

		firstNode->AddNeighbor(secondNode, Direction::East);
		secondNode->AddNeighbor(firstNode, Direction::West);
		alignment = Connection::Alignment::Vertical;
	}

	//add the node to the maze
	m_Connections.emplace_back(new Connection(firstNode, secondNode, alignment));
}

Connection* MazeComponent::GetConnection(NodeComponent* node1, NodeComponent* node2)
{
	auto it = std::find_if(m_Connections.begin(), m_Connections.end(), [node1, node2](Connection* c) {return c->Equals(node1, node2); });

	if (it == m_Connections.end()) return nullptr;
	else return (*it);
}

