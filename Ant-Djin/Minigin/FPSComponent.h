#pragma once
#include "Component.h"

namespace dae
{
	class TextComponent;
	class FPSComponent final : public Component
	{
	public:
		FPSComponent(GameObject* pGo, TextComponent* textComp);

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;


	private:
		float m_SecondsPerUpdate ;
		float m_UpdateTimer;
		int m_FrameCounter;

		TextComponent* m_pTextComp;
	};
}