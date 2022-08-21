#pragma once
#include <Component.h>
#include "RenderComponent.h"
#include "TankComponent.h"

class TankComponent;
class GunComponent final: public dae::Component
{
public:
	GunComponent(dae::GameObject* pGo, dae::RenderComponent* render, TankComponent* tank, float shotInverval, int bounces = 0, bool canAim = true);


	void Update();

	void AddRotationInput(int dir);
	void SetShootInput();



private:

	void Shoot();

	float m_ShotInverval;
	float m_ShotTimer;

	float m_BulletSpeed{100};
	int m_Bounces;

	float m_RotationSpeed{90};

	int m_RotInput;
	bool m_CanAim;
	bool m_ShootInput;

	TankComponent* m_pTank;

};
