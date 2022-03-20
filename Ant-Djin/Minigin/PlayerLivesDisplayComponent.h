#pragma once
#include "Component.h"
#include "PeterObserver.h"
#include "PeterPepperComponent.h"
namespace dae
{

	class PlayerLivesDisplayComponent final :
		public dae::Component, PeterObserver
	{
	public:
		PlayerLivesDisplayComponent(GameObject* pGo, PeterPepperComponent* peter);

		void Update() override {}
		void FixedUpdate() override {}
		void Render() const override {}


		void PlayerDied() override;
		void GainedPoints(int /*totalpoints*/) override {}

	private:
		PeterPepperComponent* m_pPeter;
		std::string CreateLivesString();
	};

}
