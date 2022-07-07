#include "TronGame.h"


#include "SceneManager.h"
#include "ServiceLocator.h"
#include "LoggerSoundSystem.h"
#include "SDLSoundSystem.h"
#include "GameObject.h"
#include "ResourceManager.h"

//components
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "MoveComponent.h"

#include <iostream>

#include "Scene.h"



using namespace dae;

void TronGame::LoadGame()
{

	Scene* pScene1 = SceneManager::GetInstance().CreateScene("scene1");

#ifdef _DEBUG
	ServiceLocator::GetInstance().RegisterSoundSystem(new LoggerSoundSystem(new SDLSoundSystem()));
#else
	ServiceLocator::GetInstance().RegisterSoundSystem(new SDLSoundSystem());
#endif 


	////SCENE 1


	//add background
	auto go = new GameObject();
	RenderComponent* renComp = go->AddComponent(new RenderComponent(go));
	Texture2D* texture = ResourceManager::GetInstance().LoadTexture("background.jpg");
	renComp->SetTexture(texture);
	pScene1->Add(go);


	//add dae logo
	go = new GameObject();
	renComp = go->AddComponent(new RenderComponent(go));
	texture = ResourceManager::GetInstance().LoadTexture("logo.png");
	renComp->SetTexture(texture);
	go->AddComponent(new MoveComponent(go));
	go->GetTransform().SetLocalPosition({ 216, 180, 0.f });
	pScene1->Add(go);

	//add the instructions text
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);
	go = new GameObject();
	renComp = go->AddComponent(new RenderComponent(go));
	go->AddComponent(new TextComponent(go, "This is Scene 1", font));
	go->GetTransform().SetLocalPosition({ 110.f, 50.f, 0.f });
	pScene1->Add(go);

	//add the fps counter
	auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 26);
	go = new GameObject();
	go->AddComponent(new RenderComponent(go));
	go->AddComponent(new TextComponent(go, "timer!", fpsFont));
	go->AddComponent(new FPSComponent(go));
	go->GetTransform().SetLocalPosition({ 0.f, 0.f, 0.f });
	pScene1->Add(go);


}
