#include "MiniginPCH.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Component.h"

dae::GameObject::GameObject(GameObject* pParent)
	:m_Transform{this}
{
	m_pParent = pParent;
	if (m_pParent != nullptr)
	{
		m_pParent->AddChild(this);
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

