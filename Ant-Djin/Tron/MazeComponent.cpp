#include "MazeComponent.h"
#include "Renderer.h"

using namespace dae;

MazeComponent::MazeComponent(GameObject* pGo) : Component(pGo)
{
	//initialize everything to do with the maze (load in from file perhaps)
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

	//render pathways

	//render connection lines
	for (Connection con : m_Connections)
	{
		Renderer::GetInstance().DrawLine(con.first->pos, con.second->pos, { 1, 1, 1, 1 });
	}
}

void MazeComponent::AddNode(Node* pNode)
{
	m_pNodes.emplace_back(pNode);
}
