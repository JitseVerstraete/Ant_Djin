#include "TankComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "GameTime.h"
#include "MazeComponent.h"
#include "RenderComponent.h"
#include "GunComponent.h"
#include "TankControllerBase.h"
#include "ResourceManager.h"
#include "ColliderComponent.h"

using namespace dae;

std::vector<TankComponent*> TankComponent::m_AllTanks = std::vector<TankComponent*>();

TankComponent::TankComponent(dae::GameObject* pGo, MazeComponent* maze, RenderComponent* renderer, TankControllerBase* controller, Team team, TankType tankType, float speed)
	: Component(pGo)
	, m_Maze{ maze }
	, m_Renderer{ renderer }
	, m_pTankController{ controller }
	, m_Team{ team }
	, m_Speed{speed}
{
	m_pCurrentNode = maze->GetSpawnPoint();
	auto spawnpos = m_pCurrentNode->GetGameObject()->GetTransform().GetWorldPosition();
	GetGameObject()->GetTransform().SetLocalPosition({ spawnpos.x, spawnpos.y, 0 });


	switch (tankType)
	{
	case TankType::Player1:
		m_Renderer->SetTexture(ResourceManager::GetInstance().LoadTexture("RedTank.png"));
		break;
	case TankType::Player2:
		m_Renderer->SetTexture(ResourceManager::GetInstance().LoadTexture("GreenTank.png"));
		break;
	case TankType::Enemy:
		m_Renderer->SetTexture(ResourceManager::GetInstance().LoadTexture("EnemyTank.png"));
		break;
	case TankType::Recognizer:
		m_Renderer->SetTexture(ResourceManager::GetInstance().LoadTexture("EnemyTank.png"));
		break;
	default:
		break;
	}

	m_Renderer->SetDestRect({ 0, 0, 32, 32 });

	m_pTankController->SetTankComponent(this);


	m_AllTanks.push_back(this);

	GetGameObject()->AddComponent(new ColliderComponent(GetGameObject(), Shape(-16, -16, 32, 32)));

}

TankComponent::~TankComponent()
{
	if (m_pTankController) delete m_pTankController;

	//remove this tank from the static list
	m_AllTanks.erase(std::remove(m_AllTanks.begin(), m_AllTanks.end(), this), m_AllTanks.end());
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

	//update gun



	//update movement
	m_MovementInput = { 0, 0 };

	m_pTankController->ProcessControlls();


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

void TankComponent::SetGun(GunComponent* gun)
{
	m_pGunComponent = gun;
}

//the tank has arrived at a node, the connection is removed
void TankComponent::ArrivedAtNode(NodeComponent* node)
{
	m_pCurrentNode = node;
	GetGameObject()->GetTransform().SetWorldPosition(m_pCurrentNode->GetGameObject()->GetTransform().GetWorldPosition());
	m_pCurrentConnection = nullptr;
}

void TankComponent::AddMovementInput(glm::ivec2 movement)
{
	m_MovementInput += movement;
}

void TankComponent::AddGunRotation(int dir)
{
	if (m_pGunComponent)
	{
		m_pGunComponent->AddRotationInput(dir);
	}
}

void TankComponent::Shoot()
{
	if (m_pGunComponent) m_pGunComponent->SetShootInput();
	else
	{
		//shoot in the direction the tank is facing

	}
}


