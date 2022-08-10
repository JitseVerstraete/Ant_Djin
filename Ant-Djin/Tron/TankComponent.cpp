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
	float xMove{};
	float yMove{};

	float elapsed = GameTime::GetInstance().GetElapsed();
	if (InputManager::GetInstance().IsPressed(SDL_SCANCODE_UP, ButtonMode::HeldDown)) yMove -= elapsed * m_Speed;
	if (InputManager::GetInstance().IsPressed(SDL_SCANCODE_DOWN, ButtonMode::HeldDown))yMove += elapsed * m_Speed;
	if (InputManager::GetInstance().IsPressed(SDL_SCANCODE_LEFT, ButtonMode::HeldDown))xMove -= elapsed * m_Speed;
	if (InputManager::GetInstance().IsPressed(SDL_SCANCODE_RIGHT, ButtonMode::HeldDown))xMove += elapsed * m_Speed;


	GetGameObject()->GetTransform().Translate({ xMove, yMove, 0.f });

}

void TankComponent::FixedUpdate()
{
}

void TankComponent::Render() const
{
}
