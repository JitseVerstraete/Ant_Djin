#pragma once
#include <Component.h>
#include "RenderComponent.h"


class GunComponent : public dae::Component
{
public:
	GunComponent(dae::GameObject* pGo, dae::RenderComponent* render);


	void Update();
	void FixedUpdate() {}
	void Render() const {}


	void Shoot();

private:

	float m_Cooldown;
	float m_ShotTimer;

	float m_BulletSpeed{100};

	float m_RotationSpeed{90};

};
