#include "MenuScene.h"
#include "InputManager.h"
#include "TronScene.h"

#include "TextComponent.h"
#include "PlayerPointsRecord.h"

using namespace dae;

void MenuScene::Initialize()
{

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
