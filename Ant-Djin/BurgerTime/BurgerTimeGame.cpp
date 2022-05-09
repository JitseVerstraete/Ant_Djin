#include "BurgerTimeGame.h"



#include "SceneManager.h"
#include "ServiceLocator.h"
#include "LoggerSoundSystem.h"
#include "SDLSoundSystem.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "ResourceManager.h"

#include <iostream>

#include "Scene.h"



using namespace dae;

void BurgerTimeGame::LoadGame()
{
	auto& scene = SceneManager::GetInstance().CreateScene("game");

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
	scene.Add(go);

	/*

	//add dae logo
	go = new GameObject();
	renComp = go->AddComponent(new RenderComponent(go));
	texture = ResourceManager::GetInstance().LoadTexture("logo.png");
	renComp->SetTexture(texture);
	go->SetPosition(216, 180);
	scene.Add(go);

	//add the instructions text
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);
	go = new GameObject();
	renComp = go->AddComponent(new RenderComponent(go));
	go->AddComponent(new TextComponent(go, "Press the A-button to play a sound", font));
	go->SetPosition(110, 50);
	scene.Add(go);

	//add the fps counter
	auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 26);
	go = new GameObject();
	go->AddComponent(new RenderComponent(go));
	go->AddComponent(new TextComponent(go, "timer!", fpsFont));
	go->AddComponent(new FPSComponent(go));
	go->SetPosition(0, 0);
	scene.Add(go);

	*/

}
