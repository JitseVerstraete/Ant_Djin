#include "MiniginPCH.h"
#include "GameScene.h"
#include "GameObject.h"

using namespace dae;


GameScene::GameScene(const std::string& name) : m_Name(name) 
{
}

GameScene::~GameScene()
{
	for (GameObject* pGO : m_Objects)
	{
		delete pGO;
	}
}

GameObject* GameScene::AddGameObject()
{
	GameObject* pNewObject = new GameObject();
	m_Objects.push_back(pNewObject);
	return pNewObject;
}

void dae::GameScene::Initialize()
{
	//body to be overriden
}

void GameScene::Update()
{
	for(auto& object : m_Objects)
	{
		object->Update();
	}
}

void GameScene::FixedUpdate()
{
	for (auto& object : m_Objects)
	{
		object->FixedUpdate();
	}
}

void GameScene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

