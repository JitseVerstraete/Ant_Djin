#include "MiniginPCH.h"
#include "PlayerScoreDisplayComponent.h"
#include "TextComponent.h"
#include "PlayerLivesDisplayComponent.h"


dae::PlayerLivesDisplayComponent::PlayerLivesDisplayComponent(GameObject* pGo, PeterPepperComponent* peter)
	:Component(pGo)
	, m_pPeter{ peter }
{
	peter->AddObserver(this);
	pGo->GetComponent<TextComponent>()->SetText(CreateLivesString());
}

void dae::PlayerLivesDisplayComponent::PlayerDied()
{
	GetGameObject()->GetComponent<TextComponent>()->SetText(CreateLivesString());
}

std::string dae::PlayerLivesDisplayComponent::CreateLivesString()
{
	return std::string("Lives: " + std::to_string(m_pPeter->GetLives()));
}

