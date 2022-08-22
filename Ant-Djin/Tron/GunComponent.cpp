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

GunComponent::GunComponent(GameObject* pGo, dae::RenderComponent* render, TankComponent* tank, float shotInverval, int bounces, bool canAim)
	: Component(pGo)
	, m_CanAim{ canAim }
	, m_pTank{tank}
	, m_ShotInverval{shotInverval}
	, m_ShotTimer{}
	, m_Bounces{bounces}
{
	if (render)render->SetTexture(ResourceManager::GetInstance().LoadTexture("RedGun.png"));
	GetGameObject()->GetTransform().SetParent(&tank->GetGameObject()->GetTransform(), false);
	tank->SetGun(this);
	GetGameObject()->m_Tag = "gun";
}

void GunComponent::Update()
{
	int rotationInput{ m_RotInput };

	//handle shooting logic
	m_ShotTimer += GameTime::GetInstance().GetElapsed();
	if (m_ShootInput && m_ShotTimer > m_ShotInverval)
	{
		Shoot();
		m_ShotTimer = 0;
	}

	//handle rotation logic
	if (m_CanAim) GetGameObject()->GetTransform().Rotate(GameTime::GetInstance().GetElapsed() * m_RotationSpeed * rotationInput);

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
	float radAngle{};
	//fire a bullet
	if (m_CanAim)
	{
		radAngle = float(M_PI / 180) * GetGameObject()->GetTransform().GetWorldRotation();
	}
	else
	{
		switch (m_pTank->GetMovementDir())
		{
		case Direction::North:
			radAngle = 3 * float(M_PI / 2);
			break;
		case Direction::South:
			radAngle = 1 * float(M_PI / 2);
			break;
		case Direction::East:
			radAngle = 0.f;
			break;
		case Direction::West:
			radAngle = 2 * float(M_PI / 2);
			break;
		default:
			break;
		}
	}

	glm::vec2 vel = { cos(radAngle), sin(radAngle) };
	vel *= m_BulletSpeed;

	auto pos = GetGameObject()->GetTransform().GetWorldPosition();

	auto pGo = SceneManager::GetInstance().GetActiveScene()->AddGameObject();
	auto renComp = pGo->AddComponent(new RenderComponent(pGo, { 0.5, 0.5 }));
	pGo->AddComponent(new BulletComponent(pGo, renComp, m_pTank->GetTeam(), pos, vel, m_Bounces));
	pGo->AddComponent(new ColliderComponent(pGo, Shape(-5, -5, 10, 10)));
	pGo->m_Tag = "bullet";
}