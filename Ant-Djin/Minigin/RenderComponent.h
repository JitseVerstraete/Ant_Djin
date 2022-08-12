#pragma once
#include "Texture2D.h"
#include "Component.h"
#include <SDL.h>

namespace dae
{
	class RenderComponent : public Component
	{
	public:
		RenderComponent(GameObject* pGo, glm::fvec2 offset = { 0.f, 0.f });
		~RenderComponent();

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void SetTexture(const std::string& filePath);
		void SetTexture(Texture2D* tex);

		void SetSourceRect(const SDL_Rect& source);
		void SetDestRect(const SDL_FRect& dest);

	private:
		Texture2D* m_pTexture{};
		glm::fvec2 m_Offset{};

		SDL_Rect* m_SourceRect{};
		SDL_FRect* m_DestRect{};

	};
}
