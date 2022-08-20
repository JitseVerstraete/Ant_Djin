#pragma once
#include <Component.h>
#include "RenderComponent.h"


class GunComponent final: public dae::Component
{
public:
	GunComponent(dae::GameObject* pGo, dae::RenderComponent* render);


	void Update();
	void FixedUpdate() {}
	void Render() const {}

	void AddRotationInput(int dir);
	void SetShootInput();

	void Shoot();

private:

	float m_Cooldown;
	float m_ShotTimer;

	float m_BulletSpeed{100};

	float m_RotationSpeed{90};

	int m_RotInput;
	bool m_ShootInput;

};
