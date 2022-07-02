#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;


Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene()
{
	for (GameObject* pGO : m_Objects)
	{
		delete pGO;
	}
}

void Scene::Add(GameObject* pObject)
{
	m_Objects.push_back(pObject);
}

void Scene::Update()
{
	for(auto& object : m_Objects)
	{
		object->Update();
	}
}

void dae::Scene::FixedUpdate()
{
	for (auto& object : m_Objects)
	{
		object->FixedUpdate();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

