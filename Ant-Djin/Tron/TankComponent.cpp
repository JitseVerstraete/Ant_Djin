#include "TankComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "GameTime.h"
#include "MazeComponent.h"
#include "RenderComponent.h"

using namespace dae;

TankComponent::TankComponent(dae::GameObject* pGo, MazeComponent* maze, RenderComponent* renderer)
	: Component(pGo)
	, m_Maze{ maze }
	, m_Renderer{renderer}
{
	m_pCurrentNode = maze->GetSpawnPoint();
	auto spawnpos = m_pCurrentNode->GetGameObject()->GetTransform().GetWorldPosition();
	GetGameObject()->GetTransform().SetLocalPosition({ spawnpos.x, spawnpos.y, 0 });


	m_Renderer->SetDestRect({ 0, 0, 32, 32 });

}

void TankComponent::Update()
{
	//update renderer settings
	switch (m_CurrentMovement)
	{
	case Direction::North:
		m_Renderer->SetSourceRect({ 32, 0, 32, 32 });
		m_Renderer->SetVerticalFlip(false);
		break;
	case Direction::South:
		m_Renderer->SetSourceRect({ 32, 0, 32, 32 });
		m_Renderer->SetVerticalFlip(true);
		break;
	case Direction::East:
		m_Renderer->SetSourceRect({ 0, 0, 32, 32 });
		m_Renderer->SetHorizontalFlip(false);
		break;
	case Direction::West:
		m_Renderer->SetSourceRect({ 0, 0, 32, 32 });
		m_Renderer->SetHorizontalFlip(true);
		break;
	default:
		break;
	}



	m_MovementInput = { 0, 0 };

	if (InputManager::GetInstance().IsPressed(SDL_SCANCODE_DOWN, ButtonMode::HeldDown)) m_MovementInput.y += -1;
	if (InputManager::GetInstance().IsPressed(SDL_SCANCODE_UP, ButtonMode::HeldDown))	m_MovementInput.y += 1;
	if (InputManager::GetInstance().IsPressed(SDL_SCANCODE_LEFT, ButtonMode::HeldDown))m_MovementInput.x += -1;
	if (InputManager::GetInstance().IsPressed(SDL_SCANCODE_RIGHT, ButtonMode::HeldDown))m_MovementInput.x += 1;

	if (m_MovementInput == glm::ivec2{ 0, 0 })
	{
		//if there is no movement input, don't move the tank
		return;
	}


	if (m_pCurrentConnection)
	{
		auto tankPos = GetGameObject()->GetTransform().GetWorldPosition();

		//check if the tank has arrived at a node (and set the position to that node)
		switch (m_pCurrentConnection->alignment)
		{
		case Connection::Alignment::Horizontal:
			if (tankPos.x > m_pCurrentConnection->second->GetGameObject()->GetTransform().GetWorldPosition().x)
			{
				ArrivedAtNode(m_pCurrentConnection->second);
			}
			else if (tankPos.x < m_pCurrentConnection->first->GetGameObject()->GetTransform().GetWorldPosition().x)
			{
				ArrivedAtNode(m_pCurrentConnection->first);
			}

			break;
		case Connection::Alignment::Vertical:
			if (tankPos.y > m_pCurrentConnection->second->GetGameObject()->GetTransform().GetWorldPosition().y)
			{
				ArrivedAtNode(m_pCurrentConnection->second);
			}
			else if (tankPos.y < m_pCurrentConnection->first->GetGameObject()->GetTransform().GetWorldPosition().y)
			{
				ArrivedAtNode(m_pCurrentConnection->first);
			}
			break;
		default:
			break;
		}

	}
	else
	{
		//===========================
		//try to set a new connection
		//===========================
		if (m_CurrentMovement == Direction::East || m_CurrentMovement == Direction::West)
		{
			//check the north/south inputs first
			if (m_MovementInput.y == 1 && m_pCurrentNode->GetNeighbor(Direction::North) != nullptr)
			{
				m_pCurrentConnection = m_Maze->GetConnection(m_pCurrentNode, m_pCurrentNode->GetNeighbor(Direction::North));
				m_CurrentMovement = Direction::North;

			}
			else if (m_MovementInput.y == -1 && m_pCurrentNode->GetNeighbor(Direction::South) != nullptr)
			{
				m_pCurrentConnection = m_Maze->GetConnection(m_pCurrentNode, m_pCurrentNode->GetNeighbor(Direction::South));
				m_CurrentMovement = Direction::South;

			}
			else if (m_MovementInput.x == 1 && m_pCurrentNode->GetNeighbor(Direction::East) != nullptr)
			{
				m_pCurrentConnection = m_Maze->GetConnection(m_pCurrentNode, m_pCurrentNode->GetNeighbor(Direction::East));
				m_CurrentMovement = Direction::East;

			}
			else if (m_MovementInput.x == -1 && m_pCurrentNode->GetNeighbor(Direction::West) != nullptr)
			{
				m_pCurrentConnection = m_Maze->GetConnection(m_pCurrentNode, m_pCurrentNode->GetNeighbor(Direction::West));
				m_CurrentMovement = Direction::West;

			}


		}
		else
		{
			//check the east/west inputs first

			if (m_MovementInput.x == 1 && m_pCurrentNode->GetNeighbor(Direction::East) != nullptr)
			{
				m_pCurrentConnection = m_Maze->GetConnection(m_pCurrentNode, m_pCurrentNode->GetNeighbor(Direction::East));
				m_CurrentMovement = Direction::East;

			}
			else if (m_MovementInput.x == -1 && m_pCurrentNode->GetNeighbor(Direction::West) != nullptr)
			{
				m_pCurrentConnection = m_Maze->GetConnection(m_pCurrentNode, m_pCurrentNode->GetNeighbor(Direction::West));
				m_CurrentMovement = Direction::West;

			}
			else if (m_MovementInput.y == 1 && m_pCurrentNode->GetNeighbor(Direction::North) != nullptr)
			{
				m_pCurrentConnection = m_Maze->GetConnection(m_pCurrentNode, m_pCurrentNode->GetNeighbor(Direction::North));
				m_CurrentMovement = Direction::North;

			}
			else if (m_MovementInput.y == -1 && m_pCurrentNode->GetNeighbor(Direction::South) != nullptr)
			{
				m_pCurrentConnection = m_Maze->GetConnection(m_pCurrentNode, m_pCurrentNode->GetNeighbor(Direction::South));
				m_CurrentMovement = Direction::South;

			}
		}

	}



	if (m_pCurrentConnection)
	{

		switch (m_pCurrentConnection->alignment)
		{
		case Connection::Alignment::Horizontal:
			if (m_MovementInput.x < 0) m_CurrentMovement = Direction::West;
			if (m_MovementInput.x > 0) m_CurrentMovement = Direction::East;

			break;
		case Connection::Alignment::Vertical:
			if (m_MovementInput.y < 0) m_CurrentMovement = Direction::South;
			if (m_MovementInput.y > 0) m_CurrentMovement = Direction::North;

			break;
		default:
			break;
		}

	}
	else return;






	//move the tank based on the movement direction
	float xMove{};
	float yMove{};
	float elapsed = GameTime::GetInstance().GetElapsed();

	switch (m_CurrentMovement)
	{
	case Direction::West:
		xMove = -m_Speed * elapsed;
		break;
	case Direction::East:
		xMove = m_Speed * elapsed;
		break;
	case Direction::North:
		yMove = -m_Speed * elapsed;
		break;
	case Direction::South:
		yMove = m_Speed * elapsed;
		break;
	default:
		break;
	}

	GetGameObject()->GetTransform().Translate({ xMove, yMove, 0.f });




}

void TankComponent::FixedUpdate()
{
}

void TankComponent::Render() const
{
}

//the tank has arrived at a node, the connection is removed
void TankComponent::ArrivedAtNode(NodeComponent* node)
{
	m_pCurrentNode = node;
	GetGameObject()->GetTransform().SetWorldPosition(m_pCurrentNode->GetGameObject()->GetTransform().GetWorldPosition());
	m_pCurrentConnection = nullptr;
}


