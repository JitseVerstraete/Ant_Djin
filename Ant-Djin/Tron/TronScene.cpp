#include "TronScene.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "MoveComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "TankComponent.h"
#include "MazeComponent.h"
#include "GunComponent.h"
#include "ColliderComponent.h"

using namespace dae;

void TronScene::Initialize()
{


	//add background
	auto go = AddGameObject();
	RenderComponent* renComp = go->AddComponent(new RenderComponent(go));
	Texture2D* texture = ResourceManager::GetInstance().LoadTexture("background.jpg");
	renComp->SetTexture(texture);



	//add the maze
	go = AddGameObject();
	auto mazeComp = go->AddComponent(new MazeComponent(go, "../Data/Levels/TestLevel.json"));
	go->GetTransform().Translate({ 0, 100 , 0 });





	
	//add tank
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);
	GameObject* parentObject = AddGameObject();
	
	renComp = parentObject->AddComponent(new RenderComponent(parentObject, glm::fvec2{ 0.5f, 0.5f }));
	renComp->SetTexture(ResourceManager::GetInstance().LoadTexture("RedTank.png"));
	//texture = ResourceManager::GetInstance().LoadTexture("logo.png");
	//renComp->SetTexture(texture);
	parentObject->AddComponent(new TankComponent(parentObject, mazeComp, renComp));

	//add tank gun
	GameObject* gun{ AddGameObject() };
	gun->GetTransform().SetParent(&parentObject->GetTransform(), false);
	auto gunRender = gun->AddComponent(new RenderComponent(gun, {0.5, 0.5}));
	gun->AddComponent(new GunComponent(gun, gunRender));


	//add the instructions text
	auto titleObject = AddGameObject();
	renComp = titleObject->AddComponent(new RenderComponent(titleObject));
	titleObject->AddComponent(new TextComponent(titleObject, "This is " + m_Name, font));
	titleObject->GetTransform().SetLocalPosition({ 110.f, 50.f, 0.f });



	//add the fps counter
	auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 26);
	go = AddGameObject();
	go->AddComponent(new RenderComponent(go));
	go->AddComponent(new TextComponent(go, "timer!", fpsFont));
	go->AddComponent(new FPSComponent(go));
	go->GetTransform().SetLocalPosition({ 0.f, 0.f, 0.f });



	go = AddGameObject();
	go->AddComponent(new ColliderComponent(go, Shape(10, 10, 100, 100)));
	go->GetTransform().Translate({ 150, 150, 0 });

	

}
