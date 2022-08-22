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
	CollisionManager* colManager = m_CollisionManager;
	m_Objects.erase(std::remove_if(m_Objects.begin(), m_Objects.end(), [colManager](GameObject* go)
		{
			if (go->MarkedForDelete())
			{
				colManager->CallExitEvent(go);
				delete go;
				return true;
			}
			return false;
		}), m_Objects.end());

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

void dae::GameScene::RemoveGameObject(GameObject* object, bool removeChildren)
{
	object->m_MarkedForDelete = true;

	if (removeChildren)
	{
		for (auto child : object->GetTransform().GetChildren())
		{
			child->GetGameObject()->m_MarkedForDelete = true;
		}
	}

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

