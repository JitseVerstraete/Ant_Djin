#pragma once
#include "Texture2D.h"
#include "Component.h"

namespace dae
{
	class RenderComponent : public Component
	{
	public:

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void SetTexture(const std::string& filePath);
		void SetTexture(std::shared_ptr<Texture2D>& tex);

	private:
		std::shared_ptr<Texture2D> m_pTexture{};
	};
}
