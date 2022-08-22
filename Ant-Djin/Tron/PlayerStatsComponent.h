#pragma once
#include "Component.h"
#include "TextComponent.h"

class TankComponent;
class PlayerStatsComponent : public dae::Component
{
public:
	PlayerStatsComponent(dae::GameObject* pGo, dae::TextComponent* text, TankComponent* tank);

	void Update() override;

private:

	dae::TextComponent* m_TextComp;
	TankComponent* m_Tank;

	int m_Points;
	int m_Lives;

};

