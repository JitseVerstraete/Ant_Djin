#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "GameTime.h"
#include "GameObject.h"
#include "TextComponent.h"
#include <iomanip>

dae::FPSComponent::FPSComponent(GameObject* pGo)
	: Component(pGo)
	, m_UpdateTimer{ m_SecondsPerUpdate }
{
}

void dae::FPSComponent::Update()
{
	TextComponent* textComp = GetGameObject()->GetComponent<TextComponent>();

	m_FrameCounter++;
	m_UpdateTimer += Time::GetInstance().GetElapsed();

	if (m_UpdateTimer > m_SecondsPerUpdate)
	{
		if (textComp == nullptr)
		{
			std::cout << "FPS COMPONENT CANT FIND A TEXTCOMPONENT ON THIS GAME OBJECT\n";
		}
		else
		{
			std::stringstream ss{};
			ss << std::fixed << std::setprecision(2) << "FPS: " << float(m_FrameCounter / m_UpdateTimer);

			textComp->SetText(ss.str());
			
		}
		m_UpdateTimer = 0.f;
		m_FrameCounter = 0;

	}


}

void dae::FPSComponent::FixedUpdate()
{
}

void dae::FPSComponent::Render() const
{
}
