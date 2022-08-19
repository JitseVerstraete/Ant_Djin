#pragma once
#include "Component.h"
#include "RenderComponent.h"


class dae::GameObject;
class BulletComponent final : public dae::Component
{
public:
	BulletComponent(dae::GameObject* pGo, dae::RenderComponent* render, const glm::vec3& pos, const glm::vec2& vel);


	void Update() override;
	void FixedUpdate() override {}
	void Render() const override {}

	void OnCollision(dae::GameObject* other, dae::CollisionType type) override;


private:
	glm::fvec2 m_Velocity{};
	bool m_BouncedThisFrame;
};

