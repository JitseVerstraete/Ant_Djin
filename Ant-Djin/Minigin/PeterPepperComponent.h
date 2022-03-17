#pragma once
#include "Component.h"
#include "PeterObserver.h"
#include <vector>
#include "InputManager.h"

namespace dae
{

	class PeterPepperComponent :
		public Component
	{
	public:
		PeterPepperComponent(GameObject* pGo,int startLives, ControllerButton dieButton, ControllerButton pointsButton) :Component(pGo), m_NrLives{ startLives }, m_dieButton{ dieButton }, m_pointsButton{ pointsButton }, m_TotalPoints{ 0 } {}

		void Update() override;
		void FixedUpdate() override {}
		void Render() const override {}

		int GetLives() { return m_NrLives; }
		int GetTotalPoints() { return  m_TotalPoints; }
		void AddObserver(PeterObserver* pObs);


	private:
		int m_NrLives;
		int m_TotalPoints{};
		const int m_PointsGain = 100;

		ControllerButton m_dieButton;
		ControllerButton m_pointsButton;
		std::vector<PeterObserver*> m_pObservers;
	};

}
