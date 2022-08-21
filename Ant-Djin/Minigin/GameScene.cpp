#include "MiniginPCH.h"
#include "GameScene.h"
#include "GameObject.h"
#include "CollisionManager.h"

using namespace dae;


GameScene::GameScene(const std::string& name)
	: m_Name(name)
	, m_Objects{}
	, m_AddQueue{}
	, m_CollisionManager{ new CollisionManager() }
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

void dae::GameScene::RemoveDeletedObjects()
{
	for (GameObject* pGo : m_Objects)
	{
		if (pGo->MarkedForDelete())
		{
			//if there is a collider attached, call exit events on all overlapping colliders before deleting
			m_CollisionManager->CallExitEvent(pGo);
			delete pGo;
			m_Objects.erase(std::remove(m_Objects.begin(), m_Objects.end(), pGo), m_Objects.end());
		}
	}
}

GameScene::~GameScene()
{
	ProcessAddQueue();
	RemoveDeletedObjects();

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

void dae::GameScene::RemoveGameObject(GameObject* object)
{

	object->m_MarkedForDelete = true;
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

