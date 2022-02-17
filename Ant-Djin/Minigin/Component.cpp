#include "MiniginPCH.h"
#include "Component.h"

void dae::Component::SetAttachedGameObject(GameObject* pGO)
{
	m_pAttachedGameObject = pGO;
}

dae::GameObject* dae::Component::GetGameObject() const
{
	return m_pAttachedGameObject;
}
