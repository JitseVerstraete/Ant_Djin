#include "MiniginPCH.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Component.h"

dae::GameObject::~GameObject()
{
	for (dae::Component* pComp : m_pComponents)
	{
		delete pComp;
		pComp = nullptr;
	}
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

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
