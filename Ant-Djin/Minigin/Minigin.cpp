#include "MiniginPCH.h"
#include "Minigin.h"
#include "BaseGame.h"



#include "ServiceLocator.h"
#include <thread>
#include "SceneManager.h"
#include "Renderer.h"
#include "GameTime.h"
#include "ResourceManager.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "PeterPepperComponent.h"
#include "PlayerScoreDisplayComponent.h"
#include "PlayerLivesDisplayComponent.h"
#include "SDLSoundSystem.h"
#include "LoggerSoundSystem.h"

using namespace std;

dae::Minigin::Minigin(BaseGame* pGame, int width, int height)
	:m_Width{ width }
	, m_Height{ height }
	, m_pGame{pGame}
{
	assert(pGame);
	srand(UINT(time(NULL)));
}

dae::Minigin::~Minigin()
{
	delete m_pGame;
}

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void dae::Minigin::Initialize()
{
	PrintSDLVersion();

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		m_Width,
		m_Height,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);


	m_pGame->SetWindowDimensions(m_Width, m_Height);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	//THIS FUNCTION IS OBSOLETE!



}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	ServiceLocator::GetInstance().Destroy();
	SceneManager::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");
	GameTime::GetInstance().Init(0.016f); //set the fixed timestep to 16ms
	ServiceLocator::GetInstance();

	m_pGame->LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto& time = GameTime::GetInstance();


		float lag{};
		bool doContinue = true;
		while (doContinue)
		{

			//PROCESS TIME
			time.ProcessTime();

			//PROCESS INPUT
			doContinue = input.ProcessInput();

			//PROCESS CURRENT SCENE (SWITCHING, ADDING/REMOVING OBJECTS)
			sceneManager.ProcessScene();

			//FIXED UPDATE 
			lag += time.GetElapsed();
			while (lag >= time.GetFixedTimeStep())
			{
				sceneManager.FixedUpdate();
				lag -= time.GetFixedTimeStep();
			}

			//UPDATE 
			sceneManager.Update();

			//RENDER
			renderer.Render();
		}
	}

	Cleanup();
}
