#pragma once
#include "Component.h"
#include "PeterObserver.h"
#include "PeterPepperComponent.h"
namespace dae
{

	class PlayerScoreDisplayComponent final :
		public dae::Component, PeterObserver
	{
	public:
		PlayerScoreDisplayComponent(GameObject* pGo, PeterPepperComponent* peter);

		void Update() override {}
		void FixedUpdate() override {}
		void Render() const override {}


		void PlayerDied() override {}
		void GainedPoints(int totalPoints) override;

	private:
		PeterPepperComponent* m_pPeter;
		std::string CreatePointsString();
	};

}
