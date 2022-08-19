#include "MiniginPCH.h"
#include "Component.h"


dae::Component::Component(GameObject* pGo) :m_pAttachedGameObject{ pGo } 
{}


dae::GameObject* dae::Component::GetGameObject() const
{
	return m_pAttachedGameObject;
}

void dae::Component::SetAttachedGameObject(GameObject* go)
{
	m_pAttachedGameObject = go;
}
