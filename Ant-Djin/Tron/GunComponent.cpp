#include "GunComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "GameTime.h"
#include "RenderComponent.h"
#include "InputManager.h"
#include "BulletComponent.h"
#include "SceneManager.h"



using namespace dae;

GunComponent::GunComponent(GameObject* pGo, dae::RenderComponent* render) : Component(pGo)
{
	render->SetTexture(ResourceManager::GetInstance().LoadTexture("RedGun.png"));
}

void GunComponent::Update()
{
	int rotationInput{};
	if (InputManager::GetInstance().IsPressed(SDL_Scancode::SDL_SCANCODE_COMMA, ButtonMode::HeldDown)) rotationInput -= 1;
	if (InputManager::GetInstance().IsPressed(SDL_Scancode::SDL_SCANCODE_PERIOD, ButtonMode::HeldDown)) rotationInput += 1;
	if (InputManager::GetInstance().IsPressed(SDL_Scancode::SDL_SCANCODE_RALT, ButtonMode::Pressed)) Shoot();


	//handle shooting logic
	GetGameObject()->GetTransform().Rotate(GameTime::GetInstance().GetElapsed() * m_RotationSpeed * rotationInput);
}

void GunComponent::Shoot()
{
	//fire a bullet
	float radAngle{ float(M_PI / 180) * GetGameObject()->GetTransform().GetWorldRotation() };
	glm::vec2 vel = { cos(radAngle), sin(radAngle) };
	vel *= m_BulletSpeed;

	auto pos = GetGameObject()->GetTransform().GetWorldPosition();

	auto pGo = SceneManager::GetInstance().GetActiveScene()->AddGameObject();
	auto renComp = pGo->AddComponent(new RenderComponent(pGo, { 0.5, 0.5 }));
	pGo->AddComponent(new BulletComponent(pGo, renComp, pos, vel));
}
