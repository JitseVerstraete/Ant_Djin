#include "MiniginPCH.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "Transform.h"
#include "SDL.h"


/* //IMGUI INCLUDES
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"
*/

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window* window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
	/* //IMGUI SETUP
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
	*/
}

void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render();

	/* //IMGUI DRAW
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_Window);
	ImGui::NewFrame();
	ImGui::ShowDemoWindow();
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	*/


	SDL_RenderPresent(m_Renderer);
}

void dae::Renderer::Destroy()
{
	/* //INGUI CLEANUP
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	*/

	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, Transform& transform, glm::fvec2 offset) const
{
	RenderTexture(texture, transform, nullptr, nullptr, SDL_RendererFlip::SDL_FLIP_NONE, offset);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, Transform& transform, SDL_Rect* source, SDL_FRect* destination, SDL_RendererFlip flip, glm::fvec2 offset) const
{
	SDL_FRect dst{};
	dst.x = transform.GetWorldPosition().x;
	dst.y = transform.GetWorldPosition().y;



	int w{}, h{};
	if (destination)
	{
		w = (int)std::round(destination->w);
		h = (int)std::round(destination->h);
	}
	else
	{
		SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &w, &h);
	}
	dst.w = w * transform.GetWorldScale().x;
	dst.h = h * transform.GetWorldScale().y;


	dst.x -= dst.w * offset.x;
	dst.y -= dst.h * offset.y;
	SDL_RenderCopyExF(GetSDLRenderer(), texture.GetSDLTexture(), source, &dst, transform.GetWorldRotation(), nullptr, flip);

}

void dae::Renderer::DrawRectangle(glm::ivec2 pos, glm::ivec2 dim, const glm::uvec4& color, bool fill)
{
	SDL_SetRenderDrawColor(GetSDLRenderer(), static_cast<Uint8>(color.r), static_cast<Uint8>(color.g), static_cast<Uint8>(color.b), static_cast<Uint8>(color.a));
	SDL_Rect rect{};
	rect.x = pos.x;
	rect.y = pos.y;
	rect.w = dim.x;
	rect.h = dim.y;

	if (fill)
	{
		SDL_RenderFillRect(GetSDLRenderer(), &rect);
	}
	else
	{
		SDL_RenderDrawRect(GetSDLRenderer(), &rect);
	}
}

void dae::Renderer::DrawLine(glm::ivec2 pos1, glm::ivec2 pos2, const glm::uvec4& color)
{
	SDL_SetRenderDrawColor(GetSDLRenderer(), static_cast<Uint8>(color.r), static_cast<Uint8>(color.g), static_cast<Uint8>(color.b), static_cast<Uint8>(color.a));
	SDL_RenderDrawLine(GetSDLRenderer(), pos1.x, pos1.y, pos2.x, pos2.y);
}




