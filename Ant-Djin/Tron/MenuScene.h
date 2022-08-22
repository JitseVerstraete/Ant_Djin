#pragma once
#include "GameScene.h"
//#include "InputManager.h"
class MenuScene : public dae::GameScene
{
public:
	MenuScene() : GameScene("menuScene") {}

protected:
	void Initialize() override;
	void SceneUpdate() override;

private:

};

