#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "Time.h"
#include "ResourceManager.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "PeterPepperComponent.h"
#include "PlayerScoreDisplayComponent.h"
#include "PlayerLivesDisplayComponent.h"
#include "SteamAchievements.h"

using namespace std;

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
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	std::cout << "CONTROLS INSTRUCTIONS:\n";
	std::cout << "Player 1 Die:	Button A\n";
	std::cout << "Player 1 Give 100 Points: Button B\n";
	std::cout << "Player 2 Die:	Button X\n";
	std::cout << "Player 2 Give 100 Points: Button Y\n";


	//add background
	auto go = std::make_shared<GameObject>();
	RenderComponent* renComp = go->AddComponent(new RenderComponent(go.get()));
	std::shared_ptr<Texture2D> texture = ResourceManager::GetInstance().LoadTexture("background.jpg");
	renComp->SetTexture(texture);
	scene.Add(go);
	/*

	//add dae logo
	go = std::make_shared<GameObject>();
	renComp = go->AddComponent(new RenderComponent());
	texture = ResourceManager::GetInstance().LoadTexture("logo.png");
	renComp->SetTexture(texture);
	go->SetPosition(216, 180);
	scene.Add(go);

	//add the demo text
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<GameObject>();
	renComp = go->AddComponent<RenderComponent>();
	TextComponent* texComp = go->AddComponent<TextComponent>();
	texComp->Init("Programming 4 Assignment", font);
	go->SetPosition(80, 20);
	scene.Add(go);
	*/

	//add the fps counter
	auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 26);
	go = std::make_shared<GameObject>();
	go->AddComponent(new RenderComponent(go.get()));
	go->AddComponent(new TextComponent(go.get(), "timer!", fpsFont));
	go->AddComponent(new FPSComponent(go.get()));
	go->SetPosition(0, 0);
	scene.Add(go);

	//make a peter pepper1 and the corresponding displays
	go = std::make_shared<GameObject>();
	auto peterComp = go->AddComponent(new PeterPepperComponent(go.get(), 3, ControllerButton::ButtonA, ControllerButton::ButtonB));
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent(new RenderComponent(go.get()));
	go->AddComponent(new TextComponent(go.get(), "Player 1:", ResourceManager::GetInstance().LoadFont("Lingua.otf", 20)));
	go->SetPosition(5.f, 300.f);
	scene.Add(go);


	go = std::make_shared<GameObject>();
	go->AddComponent(new RenderComponent(go.get()));
	go->AddComponent(new TextComponent(go.get(), "SAMPLETEXT", ResourceManager::GetInstance().LoadFont("Lingua.otf", 20)));
	go->AddComponent(new PlayerScoreDisplayComponent(go.get(), peterComp));
	go->SetPosition(5.f, 330.f);
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent(new RenderComponent(go.get()));
	go->AddComponent(new TextComponent(go.get(), "SAMPLETEXT", ResourceManager::GetInstance().LoadFont("Lingua.otf", 20)));
	go->AddComponent(new PlayerLivesDisplayComponent(go.get(), peterComp));
	go->SetPosition(5.f, 360.f);
	scene.Add(go);



	//make a peter pepper2 and the corresponding displays
	go = std::make_shared<GameObject>();
	peterComp = go->AddComponent(new PeterPepperComponent(go.get(), 3, ControllerButton::ButtonX, ControllerButton::ButtonY));
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent(new RenderComponent(go.get()));
	go->AddComponent(new TextComponent(go.get(), "Player 2:", ResourceManager::GetInstance().LoadFont("Lingua.otf", 20)));
	go->SetPosition(520.f, 300.f);
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent(new RenderComponent(go.get()));
	go->AddComponent(new TextComponent(go.get(), "SAMPLETEXT", ResourceManager::GetInstance().LoadFont("Lingua.otf", 20)));
	go->AddComponent(new PlayerScoreDisplayComponent(go.get(), peterComp));
	go->SetPosition(520.f, 330.f);
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent(new RenderComponent(go.get()));
	go->AddComponent(new TextComponent(go.get(), "SAMPLETEXT", ResourceManager::GetInstance().LoadFont("Lingua.otf", 20)));
	go->AddComponent(new PlayerLivesDisplayComponent(go.get(), peterComp));
	go->SetPosition(520.f, 360.f);
	scene.Add(go);



	auto pParent = std::make_shared<GameObject>();
	scene.Add(pParent);

	auto pChild1 = std::make_shared<GameObject>(pParent.get());
	scene.Add(pChild1);

	auto pChild2 = std::make_shared<GameObject>(pParent.get());
	scene.Add(pChild2);

}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");
	Time::GetInstance().Init(0.016f); //set the fixed timestep to 16ms

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto& time = Time::GetInstance();
		CSteamAchievements::GetInstance();



		float lag{};
		bool doContinue = true;
		while (doContinue)
		{
			SteamAPI_RunCallbacks();
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
