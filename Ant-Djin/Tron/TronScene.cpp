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
#include "TankControllerAI.h"
#include "InputManager.h"
#include "DiamondComponent.h"
#include "PlayerStatsComponent.h"
#include "PlayerPointsRecord.h"


using namespace dae;

void TronScene::Initialize()
{


	//add background
	auto go = AddGameObject();
	RenderComponent* renComp = go->AddComponent(new RenderComponent(go));
	Texture2D* texture = ResourceManager::GetInstance().LoadTexture("background.jpg");
	renComp->SetTexture(texture);
	go->GetTransform().Translate({ 0, -200, 0 });



	//add the maze
	go = AddGameObject();
	auto mazeComp = go->AddComponent(new MazeComponent(go, "../Data/Levels/TestLevel.json"));
	go->GetTransform().Translate({ 0, 100 , 0 });




	auto teleporter = AddGameObject();

	auto diamondRenderer = teleporter->AddComponent(new RenderComponent(teleporter, { 0.5f, 0.5f }));
	teleporter->AddComponent(new DiamondComponent(teleporter, diamondRenderer));
	teleporter->GetTransform().SetParent(&mazeComp->GetGameObject()->GetTransform(), false);
	teleporter->GetTransform().SetLocalPosition({ mazeComp->GetTeleporterPos().x, mazeComp->GetTeleporterPos().y, 0 });
	teleporter->AddComponent(new ColliderComponent(teleporter, { -30, -30, 60, 60 }));




	auto playerSpawns = mazeComp->GetPlayerSpawnPoints();
	auto enemySpawns = mazeComp->GetEnemySpawnPoints();

	//add player tank
	GameObject* parentObject = AddGameObject();

	renComp = parentObject->AddComponent(new RenderComponent(parentObject, glm::fvec2{ 0.5f, 0.5f }));
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

	m_PlayerTank = parentObject->AddComponent(new TankComponent(parentObject, mazeComp, playerSpawns[0], renComp, p1Controller, Team::Player, TankType::Player1, 60, m_playerSTartLives));

	m_PlayerTank->AddObserver(&PlayerPointsRecord::GetInstance());

	//add tank gun
	GameObject* gun{ AddGameObject() };
	gun->GetTransform().SetParent(&parentObject->GetTransform(), false);
	auto gunRender = gun->AddComponent(new RenderComponent(gun, { 0.5, 0.5 }));
	gun->AddComponent(new GunComponent(gun, gunRender, m_PlayerTank, 0.2f, 4, true));


	for (int i{}; i < enemySpawns.size(); ++i)
	{
		//add AI tank
		auto AiTank = AddGameObject();

		renComp = AiTank->AddComponent(new RenderComponent(AiTank, glm::fvec2{ 0.5f, 0.5f }));
		auto aiController = new TankControllerAI();
		auto AItankComp = AiTank->AddComponent(new TankComponent(AiTank, mazeComp, enemySpawns[i], renComp, aiController, Team::Enemy, TankType::Enemy, 30, 1));

		//add tank gun
		gun = AddGameObject();
		gun->GetTransform().SetParent(&AiTank->GetTransform(), false);
		gun->AddComponent(new GunComponent(gun, nullptr, AItankComp, 1.f, 0, false));

	}




	//add the stats text
	auto titleObject = AddGameObject();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 40);
	renComp = titleObject->AddComponent(new RenderComponent(titleObject));
	auto statsText = titleObject->AddComponent(new TextComponent(titleObject, "This is " + m_Name, font));
	titleObject->AddComponent(new PlayerStatsComponent(titleObject, statsText, m_PlayerTank));
	titleObject->GetTransform().SetLocalPosition({ 150.f, 50.f, 0.f });


	/*
	//add the fps counter
	auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 26);
	go = AddGameObject();
	go->AddComponent(new RenderComponent(go));
	auto textComp = go->AddComponent(new TextComponent(go, "timer!", fpsFont));
	go->AddComponent(new FPSComponent(go, textComp));
	go->GetTransform().SetLocalPosition({ 0.f, 0.f, 0.f });
	*/

}

void TronScene::SceneUpdate()
{
	//if no more players exist, go back to menu
	if (TankComponent::GetPlayerTanks().size() <= 0)
	{
		SceneManager::GetInstance().SetActiveScene("menuScene");
	}



	//if no more tanks exist, make a new tron scene
	if (TankComponent::GetEnemyTanks().size() <= 0)
	{
		SceneManager::GetInstance().AddScene(new TronScene(m_PlayerTank->GetLives()));
		SceneManager::GetInstance().SetActiveScene("tronScene");
	}


}
