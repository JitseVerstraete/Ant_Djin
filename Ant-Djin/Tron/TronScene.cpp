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
#include "TankControllerInput.h"
#include "InputManager.h"

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

	auto p1Controller = new TankControllerInput();


	p1Controller->AddBinding({ SDL_SCANCODE_UP, dae::ButtonMode::HeldDown }, TankAction::MoveUp);
	p1Controller->AddBinding({ SDL_SCANCODE_DOWN, dae::ButtonMode::HeldDown }, TankAction::MoveDown);
	p1Controller->AddBinding({ SDL_SCANCODE_LEFT, dae::ButtonMode::HeldDown }, TankAction::MoveLeft);
	p1Controller->AddBinding({ SDL_SCANCODE_RIGHT, dae::ButtonMode::HeldDown }, TankAction::MoveRight);
	p1Controller->AddBinding({ SDL_SCANCODE_COMMA, dae::ButtonMode::HeldDown }, TankAction::AimClockwise);
	p1Controller->AddBinding({ SDL_SCANCODE_PERIOD, dae::ButtonMode::HeldDown }, TankAction::AimCounterClockwise);
	p1Controller->AddBinding({ SDL_SCANCODE_RALT, dae::ButtonMode::Pressed }, TankAction::Shoot);

	parentObject->AddComponent(new TankComponent(parentObject, mazeComp, renComp, p1Controller));

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
	auto textComp = go->AddComponent(new TextComponent(go, "timer!", fpsFont));
	go->AddComponent(new FPSComponent(go, textComp));
	go->GetTransform().SetLocalPosition({ 0.f, 0.f, 0.f });

}
