#include "MiniginPCH.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "CollisionManager.h"

using namespace dae;

ColliderComponent::ColliderComponent(dae::GameObject* pGo, const Shape& shape) : Component(pGo), m_Shape{ shape }
{
	CollisionManager::GetInstance().AddCollider(this);
}

ColliderComponent::~ColliderComponent()
{
	CollisionManager::GetInstance().RemoveCollider(this);
}
