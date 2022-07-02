#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

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

void dae::SceneManager::SetActiveScene(Scene* pScene)
{
	m_pActiveScene = pScene;
}

dae::Scene* dae::SceneManager::CreateScene(const std::string& name)
{

	auto foundScene = std::find_if(m_Scenes.begin(), m_Scenes.end(), [&name](dae::Scene* s) -> bool {return s->GetName() == name; });
	if (foundScene != m_Scenes.end())
	{
		std::cout << "A SCENE WITH THAT NAME ALREADY EXISTS! Returned existing scene";
		return *foundScene;
	}
	Scene* pScene = new Scene(name);
	m_Scenes.push_back(pScene);
	if (m_pActiveScene == nullptr) m_pActiveScene = pScene;
	return pScene;
}
