#include "MiniginPCH.h"
#include "GameScene.h"
#include "GameObject.h"
#include "CollisionManager.h"

using namespace dae;


GameScene::GameScene(const std::string& name)
	: m_Name(name)
	, m_Objects{}
	, m_AddQueue{}
	, m_RemoveQueue{}
	, m_CollisionManager{new CollisionManager()}
{
}

void dae::GameScene::ProcessAddQueue()
{
	for (GameObject* pGo : m_AddQueue)
	{
		m_Objects.emplace_back(pGo);
	}

	m_AddQueue.clear();
}

void dae::GameScene::ProcessRemoveQueue()
{
	for (GameObject* pGo : m_RemoveQueue)
	{
		if (pGo) delete pGo;
		m_Objects.erase(std::remove(m_Objects.begin(), m_Objects.end(), pGo), m_Objects.end());
	}

	m_RemoveQueue.clear();
}

GameScene::~GameScene()
{
	ProcessAddQueue();
	ProcessRemoveQueue();

	for (GameObject* pGO : m_Objects)
	{
		delete pGO;
	}

	delete m_CollisionManager;
}

GameObject* GameScene::AddGameObject()
{
	GameObject* pNewObject = new GameObject();
	pNewObject->m_Scene = this;
	m_AddQueue.push_back(pNewObject);
	return pNewObject;
}

void dae::GameScene::Initialize()
{
	//body to be overriden
}

void GameScene::Update()
{
	for (auto& object : m_Objects)
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

