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

private:
	float m_Cooldown;
	float m_ShotTimer;

	float m_Angle;
	float m_RotationSpeed{90};



};
