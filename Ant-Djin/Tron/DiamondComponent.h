#pragma once
#include <Component.h>
#include "RenderComponent.h"

class DiamondComponent final : public dae::Component
{
public:
	DiamondComponent(dae::GameObject* pGo, dae::RenderComponent* renderComp);
	~DiamondComponent() = default;
};

