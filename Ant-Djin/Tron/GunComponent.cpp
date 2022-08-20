#include "GunComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "GameTime.h"
#include "RenderComponent.h"
#include "InputManager.h"
#include "BulletComponent.h"
#include "SceneManager.h"
#include "ColliderComponent.h"
#include "TankComponent.h"



using namespace dae;

GunComponent::GunComponent(GameObject* pGo, dae::RenderComponent* render, TankComponent* tank) 
	: Component(pGo)
{
	render->SetTexture(ResourceManager::GetInstance().LoadTexture("RedGun.png"));
	GetGameObject()->GetTransform().SetParent(&tank->GetGameObject()->GetTransform(), false);
	tank->SetGun(this);
}

void GunComponent::Update()
{
	int rotationInput{m_RotInput};
	if (m_ShootInput) Shoot();


	//handle shooting logic
	GetGameObject()->GetTransform().Rotate(GameTime::GetInstance().GetElapsed() * m_RotationSpeed * rotationInput);

	m_RotInput = 0;
	m_ShootInput = false;
}

void GunComponent::AddRotationInput(int dir)
{
	m_RotInput += dir;
}

void GunComponent::SetShootInput()
{
	m_ShootInput = true;
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
	pGo->AddComponent(new ColliderComponent(pGo, Shape(-5, -5, 10, 10)));
}
