#include "TestScene.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "MoveComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"

using namespace dae;

void TestScene::Initialize()
{


	//add background
	auto go = new GameObject();
	RenderComponent* renComp = go->AddComponent(new RenderComponent(go));
	Texture2D* texture = ResourceManager::GetInstance().LoadTexture("background.jpg");
	renComp->SetTexture(texture);
	Add(go);


	//add dae logo
	GameObject* parentObject = new GameObject();
	renComp = parentObject->AddComponent(new RenderComponent(parentObject));
	texture = ResourceManager::GetInstance().LoadTexture("logo.png");
	renComp->SetTexture(texture);
	parentObject->AddComponent(new MoveComponent(parentObject));
	parentObject->GetTransform().SetLocalPosition({ 216, 180, 0.f });
	Add(parentObject);

	//add the instructions text
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);
	go = new GameObject();
	renComp = go->AddComponent(new RenderComponent(go));
	go->AddComponent(new TextComponent(go, "This is Scene 1", font));
	go->GetTransform().SetLocalPosition({ 110.f, 50.f, 0.f });
	go->GetTransform().SetParent(&parentObject->GetTransform());
	Add(go);

	//add the fps counter
	auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 26);
	go = new GameObject();
	go->AddComponent(new RenderComponent(go));
	go->AddComponent(new TextComponent(go, "timer!", fpsFont));
	go->AddComponent(new FPSComponent(go));
	go->GetTransform().SetLocalPosition({ 0.f, 0.f, 0.f });
	Add(go);

}
