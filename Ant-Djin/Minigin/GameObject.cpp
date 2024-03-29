#include "MiniginPCH.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Component.h"

dae::GameObject::GameObject()
	:m_Transform{this}
	, m_MarkedForDelete{false}
{
}

void dae::GameObject::OnCollision(GameObject* other, CollisionType type)
{
	for (Component* comp : m_pComponents)
	{
		comp->OnCollision(other, type);
	}
}

dae::GameObject::~GameObject()
{
	for (dae::Component* pComp : m_pComponents)
	{
		delete pComp;
		pComp = nullptr;
	}
	
	/* todo: make it possible to delete all children when you remove the parent
	for (GameObject* pChild : m_pChildren)
	{
		if (pChild != nullptr) delete pChild;
	}
	*/
}

bool dae::GameObject::MarkedForDelete()
{
	return m_MarkedForDelete;
}

void dae::GameObject::Update()
{
	for (dae::Component* pComp : m_pComponents)
	{
		pComp->Update();
	}
}

void dae::GameObject::FixedUpdate()
{
	for (dae::Component* pComp : m_pComponents)
	{
		pComp->FixedUpdate();
	}
}

void dae::GameObject::Render() const
{
	for (dae::Component* pComp : m_pComponents)
	{
		pComp->Render();
	}
}

