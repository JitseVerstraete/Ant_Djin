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
{
	assert(pGame);
	m_pGame = pGame;
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


	/*
	Scene* pScene = SceneManager::GetInstance().CreateScene("Demo");

#ifdef _DEBUG
	ServiceLocator::GetInstance().RegisterSoundSystem(new LoggerSoundSystem(new SDLSoundSystem()));
#else
	ServiceLocator::GetInstance().RegisterSoundSystem(new SDLSoundSystem());
#endif


	std::cout << "\nCONTROLS INSTRUCTIONS\n===============================\n";
	std::cout << "Press the A-buton to play a sound\n";


	//add background
	auto go = new GameObject();
	RenderComponent* renComp = go->AddComponent(new RenderComponent(go));
	Texture2D* texture = ResourceManager::GetInstance().LoadTexture("background.jpg");
	renComp->SetTexture(texture);
	pScene->Add(go);

	//add dae logo
	go = new GameObject();
	renComp = go->AddComponent(new RenderComponent(go));
	texture = ResourceManager::GetInstance().LoadTexture("logo.png");
	renComp->SetTexture(texture);
	go->GetTransform().pos = { 216.f, 180.f, 0.f };
	pScene->Add(go);

	//add the instructions text
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);
	go = new GameObject();
	renComp = go->AddComponent(new RenderComponent(go));
	go->AddComponent(new TextComponent(go, "Press the A-button to play a sound", font));
	go->GetTransform().pos = { 110.f, 50.f, 0.f };
	pScene->Add(go);

	//add the fps counter
	auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 26);
	go = new GameObject();
	go->AddComponent(new RenderComponent(go));
	go->AddComponent(new TextComponent(go, "timer!", fpsFont));
	go->AddComponent(new FPSComponent(go));
	go->GetTransform().pos = { 0.f, 0.f, 0.f };
	pScene->Add(go);


	std::cout << "CONTROLS INSTRUCTIONS:\n";
	std::cout << "Player 1 Die:	Button A\n";
	std::cout << "Player 1 Give 100 Points: Button B\n";
	std::cout << "Player 2 Die:	Button X\n";
	std::cout << "Player 2 Give 100 Points: Button Y\n";
	*/

	/* Events code (not needed now)
	*
	//make a peter pepper1 and the corresponding displays
	go = new GameObject();
	auto peterComp = go->AddComponent(new PeterPepperComponent(go, 3, ControllerButton::ButtonA, ControllerButton::ButtonB));
	scene.Add(go);



	go = new GameObject();
	go->AddComponent(new RenderComponent(go));
	go->AddComponent(new TextComponent(go, "Player 1:", ResourceManager::GetInstance().LoadFont("Lingua.otf", 20)));
	go->SetPosition(5.f, 300.f);
	scene.Add(go);


	go = new GameObject();
	go->AddComponent(new RenderComponent(go));
	go->AddComponent(new TextComponent(go, "SAMPLETEXT", ResourceManager::GetInstance().LoadFont("Lingua.otf", 20)));
	go->AddComponent(new PlayerScoreDisplayComponent(go, peterComp));
	go->SetPosition(5.f, 330.f);
	scene.Add(go);

	go = new GameObject();
	go->AddComponent(new RenderComponent(go));
	go->AddComponent(new TextComponent(go, "SAMPLETEXT", ResourceManager::GetInstance().LoadFont("Lingua.otf", 20)));
	go->AddComponent(new PlayerLivesDisplayComponent(go, peterComp));
	go->SetPosition(5.f, 360.f);
	scene.Add(go);



	//make a peter pepper2 and the corresponding displays
	go = new GameObject();
	peterComp = go->AddComponent(new PeterPepperComponent(go, 3, ControllerButton::ButtonX, ControllerButton::ButtonY));
	scene.Add(go);

	go = new GameObject();
	go->AddComponent(new RenderComponent(go));
	go->AddComponent(new TextComponent(go, "Player 2:", ResourceManager::GetInstance().LoadFont("Lingua.otf", 20)));
	go->SetPosition(520.f, 300.f);
	scene.Add(go);

	go = new GameObject();
	go->AddComponent(new RenderComponent(go));
	go->AddComponent(new TextComponent(go, "SAMPLETEXT", ResourceManager::GetInstance().LoadFont("Lingua.otf", 20)));
	go->AddComponent(new PlayerScoreDisplayComponent(go, peterComp));
	go->SetPosition(520.f, 330.f);
	scene.Add(go);

	go = new GameObject();
	go->AddComponent(new RenderComponent(go));
	go->AddComponent(new TextComponent(go, "SAMPLETEXT", ResourceManager::GetInstance().LoadFont("Lingua.otf", 20)));
	go->AddComponent(new PlayerLivesDisplayComponent(go, peterComp));
	go->SetPosition(520.f, 360.f);
	scene.Add(go);
	 */
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	ServiceLocator::GetInstance().Destroy();
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
