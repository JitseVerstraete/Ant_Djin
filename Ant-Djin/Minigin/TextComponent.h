#pragma once
#include "Transform.h"
#include "Font.h"
#include "Component.h"

namespace dae
{
	class TextComponent : public Component
	{
	public:
		TextComponent(GameObject* pGo,const std::string& text, std::shared_ptr<Font> font);

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void SetText(const std::string& newText);


		

	private:
		bool m_NeedsUpdate = true;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;

	};
}