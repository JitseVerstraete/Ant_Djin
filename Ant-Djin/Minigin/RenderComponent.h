#pragma once
#include "Texture2D.h"
#include "Component.h"

namespace dae
{
	class RenderComponent : public Component
	{
	public:
		RenderComponent(GameObject* pGo);

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void SetTexture(const std::string& filePath);
		void SetTexture(Texture2D* tex);

	private:
		Texture2D* m_pTexture{};
	};
}
