#include "MazeComponent.h"
#include "Renderer.h"
#include <iostream>
#include "GameObject.h"
#include "SceneManager.h"
#include "GameScene.h"

using namespace dae;




NodeComponent::NodeComponent(GameObject* pGo, int x, int y)
	:Component(pGo)
{
	GetGameObject()->GetTransform().SetLocalPosition({ x, y, 0 });
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

	AddNode(testNode1);
	AddNode(testNode2); 
	AddNode(testNode3);

	AddConnection(testNode1, testNode2);
	AddConnection(testNode2, testNode3);

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
	Renderer::GetInstance().DrawRectangle({ GetGameObject()->GetTransform().GetWorldPosition().x,GetGameObject()->GetTransform().GetWorldPosition().y }, { m_MazeDimensions, m_MazeDimensions }, { 0, 170, 0, 255 });
	

	//render pathways
	for (Connection con : m_Connections)
	{
		glm::ivec3 firstPos = con.first->GetGameObject()->GetTransform().GetWorldPosition();
		glm::ivec3 secondPos = con.second->GetGameObject()->GetTransform().GetWorldPosition();

		int rectWidth{ m_PathWidth * 2 + abs(firstPos.x - secondPos.x) };
		int rechtHeight{ m_PathWidth * 2 + abs(firstPos.y - secondPos.y) };
		Renderer::GetInstance().DrawRectangle({ firstPos.x - m_PathWidth , firstPos.y - m_PathWidth }, { rectWidth, rechtHeight }, { 0, 0, 0, 255 });
	}

	//render nodes


	//render connection lines
	for (Connection con : m_Connections)
	{
		Renderer::GetInstance().DrawLine(	glm::ivec2( con.first->GetGameObject()->GetTransform().GetWorldPosition()), 
											glm::ivec2(con.second->GetGameObject()->GetTransform().GetWorldPosition()),
											{ 255, 0, 0, 255 });
	}
}

void MazeComponent::AddNode(NodeComponent* pNode)
{
	m_pNodes.emplace_back(pNode);
}

void MazeComponent::AddConnection(NodeComponent* first, NodeComponent* second)
{
	glm::ivec3 firstPos = first->GetGameObject()->GetTransform().GetLocalPosition();
	glm::ivec3 secondPos = second->GetGameObject()->GetTransform().GetLocalPosition();
	bool xSame{ firstPos.x == secondPos.x };
	bool ySame{ firstPos.y == secondPos.y };

	//check if the nodes are aligned horizontally or vertically
	if (!xSame && !ySame)
	{
		std::cout << "Connection not possible, the nodes are not alligned horizontally or vertically\n";
		return;
	}

	//check if the nodes have a different pos
	if (firstPos == secondPos)
	{
		std::cout << "Connection not possible, nodes have the same position";
		return;
	}

	//add the node to the maze
	m_Connections.emplace_back(Connection(first, second));



	if (xSame)
	{
		if (firstPos.y < secondPos.y)
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
		if (firstPos.x < secondPos.x)
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

