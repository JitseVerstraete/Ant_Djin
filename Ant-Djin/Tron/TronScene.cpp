#include "TronScene.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "MoveComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "TankComponent.h"
#include "MazeComponent.h"

using namespace dae;

void TronScene::Initialize()
{

	
	//add background
	auto go = new GameObject();
	RenderComponent* renComp = go->AddComponent(new RenderComponent(go));
	Texture2D* texture = ResourceManager::GetInstance().LoadTexture("background.jpg");
	renComp->SetTexture(texture);
	//Add(go);


	//add the maze
	go = new GameObject();
	go->AddComponent(new MazeComponent(go, 640));
	go->GetTransform().Translate({ 0, 100 , 0});

	Add(go);
	


	//add dae logo
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);
	GameObject* parentObject = new GameObject();
	renComp = parentObject->AddComponent(new RenderComponent(parentObject));
	parentObject->AddComponent(new TextComponent(parentObject, "tank", font));
	//texture = ResourceManager::GetInstance().LoadTexture("logo.png");
	//renComp->SetTexture(texture);
	parentObject->AddComponent(new TankComponent(parentObject));
	parentObject->GetTransform().SetLocalPosition({ 216, 180, 0.f });
	Add(parentObject);

	//add the instructions text
	auto titleObject = new GameObject();
	renComp = titleObject->AddComponent(new RenderComponent(titleObject));
	titleObject->AddComponent(new TextComponent(titleObject, "This is " + m_Name, font));
	titleObject->GetTransform().SetLocalPosition({ 110.f, 50.f, 0.f });
	Add(titleObject);

	//add the fps counter
	auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 26);
	go = new GameObject();
	go->AddComponent(new RenderComponent(go));
	go->AddComponent(new TextComponent(go, "timer!", fpsFont));
	go->AddComponent(new FPSComponent(go));
	go->GetTransform().SetLocalPosition({ 0.f, 0.f, 0.f });
	Add(go);


}
