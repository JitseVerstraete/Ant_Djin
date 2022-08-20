#pragma once
#include "Transform.h"
#include "Font.h"
#include "Component.h"
#include "Texture2D.h"

namespace dae
{
	class RenderComponent;
	class TextComponent final : public Component
	{
	public:
		TextComponent(GameObject* pGo, const std::string& text, Font* font);
		~TextComponent();

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void SetText(const std::string& newText);



	private:
		bool m_NeedsUpdate = true;
		std::string m_Text;
		Font* m_pFont;
		Texture2D* m_pTempTexture;
		RenderComponent* m_RenderComp;

	};
}