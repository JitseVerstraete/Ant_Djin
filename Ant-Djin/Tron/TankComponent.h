#pragma once
#include "Component.h"




class TankComponent : public dae::Component
{
public:
	class GameObject;
	TankComponent(dae::GameObject* pGo);

	void Update() override;
	void FixedUpdate() override;
	void Render() const override;

private:

	float m_Speed = 50.f;

};

