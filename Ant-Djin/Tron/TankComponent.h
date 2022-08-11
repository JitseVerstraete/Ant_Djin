#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include "MazeComponent.h"

class TankComponent : public dae::Component
{
public:
	class GameObject;
	TankComponent(dae::GameObject* pGo, MazeComponent* maze);

	void Update() override;
	void FixedUpdate() override;
	void Render() const override;

private:

	float m_Speed = 50.f;
	MazeComponent* m_Maze;

	Direction m_CurrentMovement{};
	glm::ivec2 m_MovementInput;

	Connection* m_CurrentConnection{ nullptr };

	NodeComponent* m_pStartNode;

};

