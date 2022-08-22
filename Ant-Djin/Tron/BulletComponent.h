#pragma once
#include "Component.h"
#include "RenderComponent.h"
#include "TankComponent.h"


class dae::GameObject;
class BulletComponent final : public dae::Component
{
public:
	BulletComponent(dae::GameObject* pGo, dae::RenderComponent* render, Team team, const glm::vec3& pos, const glm::vec2& vel, int bounces);


	void Update() override;
	void FixedUpdate() override {}
	void Render() const override {}

	void OnCollision(dae::GameObject* other, dae::CollisionType type) override;

	Team GetTeam() const { return m_Team; } 


private:
	glm::fvec2 m_Velocity{};
	bool m_BouncedThisFrame;
	int m_Bounces;
	Team m_Team;
};

