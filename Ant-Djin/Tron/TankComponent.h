#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include "RenderComponent.h"
#include "MazeComponent.h"

class TankComponent : public dae::Component
{
public:
	class GameObject;
	TankComponent(dae::GameObject* pGo, MazeComponent* maze, dae::RenderComponent* renderer);

	void Update() override;
	void FixedUpdate() override;
	void Render() const override;

private:

	float m_Speed = 50.f;
	MazeComponent* m_Maze;
	dae::RenderComponent* m_Renderer;

	Direction m_CurrentMovement{};
	glm::ivec2 m_MovementInput;

	//data used to navigate the maze
	Connection* m_pCurrentConnection{ nullptr }; 
	NodeComponent* m_pCurrentNode; 


	void ArrivedAtNode(NodeComponent* node);
};

