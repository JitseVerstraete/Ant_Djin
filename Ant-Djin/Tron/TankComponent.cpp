#include "TankComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "GameTime.h"
#include "MazeComponent.h"


using namespace dae;

TankComponent::TankComponent(dae::GameObject* pGo, MazeComponent* maze)
	: Component(pGo)
	, m_Maze{ maze }
{
	//todo: setup what sprite should be used, what commands should be made (and sent where)
	auto spawnpos = maze->GetSpawnPoint()->GetGameObject()->GetTransform().GetWorldPosition();
	GetGameObject()->GetTransform().SetLocalPosition({ spawnpos.x, spawnpos.y, 0 });

}

void TankComponent::Update()
{
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



	//////selecte the movement direction, based on what node you are going to (and where you came from)
	
	//when on a connection
	//(when pressing input in the opposite direction, change direction, otherwise keep moving in the current direction)

	//when on a node
	//if there is input to take a turn, set the new connection.
	
	

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
