#include "DiamondComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"

using namespace dae;

DiamondComponent::DiamondComponent(GameObject* pGo, dae::RenderComponent* renderComp)
	: Component(pGo)
{
	renderComp->SetTexture(ResourceManager::GetInstance().LoadTexture("Diamond.png"));
	renderComp->SetDestRect({ 0, 0, 100, 100 });
	GetGameObject()->m_Tag =  "teleporter";
}

