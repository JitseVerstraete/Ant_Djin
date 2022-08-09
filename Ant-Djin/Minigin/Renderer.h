#pragma once
#include "Singleton.h"

#include <SDL.h>
namespace dae
{
	class Transform;
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_Renderer{};
		SDL_Window* m_Window{};
		SDL_Color m_clearColor{};	
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, Transform& transform) const;
		void DrawRectangle(glm::ivec2 pos, glm::ivec2 dim, const glm::uvec4& color, bool fill= true);
		void DrawLine(glm::ivec2 pos1, glm::ivec2 pos2, const glm::uvec4& color);

		

		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
	};
}

