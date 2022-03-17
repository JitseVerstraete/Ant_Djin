#include "MiniginPCH.h"
#include "PlayerScoreDisplayComponent.h"
#include "TextComponent.h"


dae::PlayerScoreDisplayComponent::PlayerScoreDisplayComponent(GameObject* pGo, PeterPepperComponent* peter )
	:Component(pGo)
	,m_pPeter{ peter }
{
	peter->AddObserver(this);
	pGo->GetComponent<TextComponent>()->SetText(CreatePointsString());
}

void dae::PlayerScoreDisplayComponent::GainedPoints()
{
	GetGameObject()->GetComponent<TextComponent>()->SetText(CreatePointsString());
}

std::string dae::PlayerScoreDisplayComponent::CreatePointsString()
{
	return std::string("Score: " + std::to_string( m_pPeter->GetTotalPoints()));
}
