#pragma once
#include "Component.h"

namespace dae
{
	class FPSComponent : public Component
	{
	public:
		FPSComponent();

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;


	private:
		float m_SecondsPerUpdate = 1.f;
		float m_UpdateTimer = 0.f;
		int m_FrameCounter = 0;

	};
}