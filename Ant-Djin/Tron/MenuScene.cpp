#include "MenuScene.h"
#include "InputManager.h"
#include "TronScene.h"

#include "TextComponent.h"
#include "PlayerPointsRecord.h"
#include "ResourceManager.h"

using namespace dae;

void MenuScene::Initialize()
{

	//add the title text
	auto go = AddGameObject();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 40);
	auto renComp = go->AddComponent(new RenderComponent(go));
	go->AddComponent(new TextComponent(go, "TRON", font));
	go->GetTransform().SetLocalPosition({ 150.f, 50.f, 0.f });


	//add the highscores title text
	go = AddGameObject();
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 30);
	renComp = go->AddComponent(new RenderComponent(go));
	go->AddComponent(new TextComponent(go, "HIGHSCORES:", font));
	go->GetTransform().SetLocalPosition({ 150.f, 150.f, 0.f });


	auto scores = PlayerPointsRecord::GetInstance().ReadScoresFromFile("../Data/HighScores.txt");



	for (int i{}; i < 5; ++i)
	{
		//add the highscore text
		go = AddGameObject();
		font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);
		renComp = go->AddComponent(new RenderComponent(go));

		std::string text{};
		if (i < (int)scores.size())
		{
			text = std::to_string(i).append(": ").append(std::to_string(scores[i]));
		}
		else
		{
			text = std::to_string(i).append(": ").append(std::to_string(0));
		}
		go->AddComponent(new TextComponent(go, text, font));
		go->GetTransform().SetLocalPosition({ 150.f, 200.f + (40.f * i), 0.f });

	}

	//add the highscores title text
	go = AddGameObject();
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 30);
	renComp = go->AddComponent(new RenderComponent(go));
	go->AddComponent(new TextComponent(go, "PRESS 1 TO START!:", font));
	go->GetTransform().SetLocalPosition({ 150.f, 500.f, 0.f });



}

void MenuScene::SceneUpdate()
{
	std::string sceneName{};


	if (InputManager::GetInstance().IsPressed(SDL_SCANCODE_1, ButtonMode::Pressed))
	{
		PlayerPointsRecord::GetInstance().ResetScores();
		SceneManager::GetInstance().AddScene(new TronScene(3));
		SceneManager::GetInstance().SetActiveScene("tronScene");
	};



}
