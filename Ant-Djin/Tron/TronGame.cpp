#include "TronGame.h"


#include "SceneManager.h"
#include "ServiceLocator.h"
#include "LoggerSoundSystem.h"
#include "SDLSoundSystem.h"
#include "GameObject.h"
#include "ResourceManager.h"

//components includes
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "MoveComponent.h"

#include <iostream>

#include "MenuScene.h"



using namespace dae;

void TronGame::LoadGame()
{


#ifdef _DEBUG
	ServiceLocator::GetInstance().RegisterSoundSystem(new LoggerSoundSystem(new SDLSoundSystem()));
#else
	ServiceLocator::GetInstance().RegisterSoundSystem(new SDLSoundSystem());
#endif 

	////SCENE 1
	SceneManager::GetInstance().AddScene(new MenuScene());



}
