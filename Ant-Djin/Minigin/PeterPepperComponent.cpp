#include "MiniginPCH.h"
#include "PeterPepperComponent.h"

void dae::PeterPepperComponent::Update()
{
	if (InputManager::GetInstance().IsPressed(m_dieButton, ButtonMode::Pressed, 0))
	{
		m_NrLives--;
		for (auto pObs : m_pObservers)
		{
			pObs->PlayerDied();
		}
	}


	if (InputManager::GetInstance().IsPressed(m_pointsButton, ButtonMode::Pressed, 0))
	{
		m_TotalPoints += m_PointsGain;
		for (auto pObs : m_pObservers)
		{
			pObs->GainedPoints();
		}
	}
}

void dae::PeterPepperComponent::AddObserver(PeterObserver* pObs)
{
	if (pObs != nullptr)
	{
		m_pObservers.push_back(pObs);
	}
}
