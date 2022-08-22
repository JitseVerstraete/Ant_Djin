#include "PlayerStatsComponent.h"
#include "TankComponent.h"
#include "PlayerPointsRecord.h"

using namespace dae;


PlayerStatsComponent::PlayerStatsComponent(GameObject* pGo, TextComponent* text, TankComponent* tank)
	:Component(pGo)
	, m_Points{}
	, m_Lives{}
	, m_TextComp{text}
	, m_Tank{tank}
{
}

void PlayerStatsComponent::Update()
{

	auto points = std::to_string(PlayerPointsRecord::GetInstance().GetPointsP1());
	auto lives = std::to_string(m_Tank->GetLives());

	std::string text = "points: " + points + "   Lives: " + lives;
	m_TextComp->SetText(text);
}
