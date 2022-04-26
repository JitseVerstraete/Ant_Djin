#include "MiniginPCH.h"
#include "TextComponent.h"
#include <SDL_ttf.h>
#include "Renderer.h"
#include "GameObject.h"
#include "RenderComponent.h"

dae::TextComponent::TextComponent(GameObject* pGo, const std::string& text, Font* font)
	: Component(pGo)
	, m_Text{ text }
	, m_NeedsUpdate{ true }
	, m_pFont{ font }
{
}

dae::TextComponent::~TextComponent()
{
	if (m_pTempTexture)
	{
		delete m_pTempTexture;
	}
}


void dae::TextComponent::Update()
{

	//if needs update, find a rendercomponent and set the new texture2d to the newly made texture with text&font
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now

		RenderComponent* renComp = GetGameObject()->GetComponent<RenderComponent>();
		if (renComp == nullptr)
		{
			std::cout << "TEXT COMPONENT COULDN'T FIND A RENDER COMPONENT\n";

		}
		else
		{
			const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
			if (surf == nullptr)
			{
				throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
			}
			auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
			if (texture == nullptr)
			{
				throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
			}
			SDL_FreeSurface(surf);
			auto newTex = new Texture2D(texture);


			if (m_pTempTexture)
			{
				delete m_pTempTexture;
			}

			m_pTempTexture = newTex;
			renComp->SetTexture(m_pTempTexture);

		}

		m_NeedsUpdate = false;
	}

}

void dae::TextComponent::FixedUpdate()
{
}

void dae::TextComponent::Render() const
{
}

void dae::TextComponent::SetText(const std::string& newText)
{
	m_Text = newText;
	m_NeedsUpdate = true;
}

