#pragma once
#include "Transform.h"
#include "Font.h"
#include "Component.h"

namespace dae
{
	class TextComponent : public Component
	{
	public:
		TextComponent();

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void SetText(const std::string& newText);


		void Init(const std::string& text, std::shared_ptr<Font> font);
		

	private:
		bool m_NeedsUpdate = true;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;

	};
}