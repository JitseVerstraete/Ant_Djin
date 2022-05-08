#pragma once
struct SDL_Window;
class BaseGame;
namespace dae
{
	class Minigin final
	{
	public:
		Minigin(BaseGame* pGame);
		~Minigin();
		Minigin(const Minigin& other) = delete;
		Minigin(const Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(const Minigin&& other) = delete;

		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
		BaseGame* m_pGame;
	};
}