#pragma once
#include "Texture2D.h"
#include "Component.h"
#include <string>
#include <SDL.h>
#include <glm/glm.hpp>

namespace dae
{
	class GameObject;
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

		void SetHorizontalFlip(bool value);
		void SetVerticalFlip(bool value);
		

	private:
		Texture2D* m_pTexture{};
		glm::fvec2 m_Offset{};

		SDL_Rect* m_SourceRect{};
		SDL_FRect* m_DestRect{};

		bool m_HorizontalFlip{};
		bool m_VerticalFlip{};

	};
}
