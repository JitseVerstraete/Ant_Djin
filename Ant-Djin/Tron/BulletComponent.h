#pragma once
#include <Component.h>
#include "RenderComponent.h"



class BulletComponent : public dae::Component
{
public:
	BulletComponent(dae::GameObject* pGo, dae::RenderComponent* render, const glm::vec3& pos, const glm::vec2& vel);


	void Update() override;
	void FixedUpdate() override {}
	void Render() const override {}


private:
	glm::fvec2 m_Velocity{};
};

