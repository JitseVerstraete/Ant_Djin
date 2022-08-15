#include "MenuScene.h"
#include "InputManager.h"
#include "TronScene.h"

using namespace dae;

void MenuScene::Initialize()
{

}

void MenuScene::SceneUpdate()
{
	std::string sceneName{};


	if (InputManager::GetInstance().IsPressed(SDL_SCANCODE_1, ButtonMode::Pressed)) sceneName = "solo Game";
	else if (InputManager::GetInstance().IsPressed(SDL_SCANCODE_2, ButtonMode::Pressed)) sceneName = "coop Game";
	else if (InputManager::GetInstance().IsPressed(SDL_SCANCODE_3, ButtonMode::Pressed)) sceneName = "versus Game";
	else return;
	SceneManager::GetInstance().AddScene(new TronScene(sceneName));
	SceneManager::GetInstance().SetActiveScene(sceneName);


}
