#include "MiniginPCH.h"
#include "SceneManager.h"
#include "GameScene.h"

void dae::SceneManager::Update()
{
	if (m_pActiveScene)
	{
		m_pActiveScene->Update();
	}
}

void dae::SceneManager::FixedUpdate()
{
	if (m_pActiveScene)
	{
		m_pActiveScene->FixedUpdate();
	}
}

void dae::SceneManager::Render()
{
	if (m_pActiveScene)
	{
		m_pActiveScene->Render();
	}
}

void dae::SceneManager::SetActiveScene(GameScene* pScene)
{
	m_pActiveScene = pScene;
}

dae::GameScene* dae::SceneManager::CreateEmptyScene(const std::string& name)
{

	auto foundScene = std::find_if(m_Scenes.begin(), m_Scenes.end(), [&name](dae::GameScene* s) -> bool {return s->GetName() == name; });
	if (foundScene != m_Scenes.end())
	{
		std::cout << "A SCENE WITH THAT NAME ALREADY EXISTS!";
		return nullptr;
	}
	GameScene* pScene = new GameScene(name);
	m_Scenes.push_back(pScene);
	if (m_pActiveScene == nullptr) m_pActiveScene = pScene;
	return pScene;
}

void dae::SceneManager::AddScene(GameScene* pScene)
{
	auto foundScene = std::find_if(m_Scenes.begin(), m_Scenes.end(), [&name = pScene->GetName()](dae::GameScene* s) -> bool {return s->GetName() == name; });
	if (foundScene != m_Scenes.end())
	{
		std::cout << "A SCENE WITH THAT NAME ALREADY EXISTS!";
		return;
	}

	m_Scenes.push_back(pScene);
	pScene->Initialize();
	if (m_pActiveScene == nullptr) m_pActiveScene = pScene;
}
