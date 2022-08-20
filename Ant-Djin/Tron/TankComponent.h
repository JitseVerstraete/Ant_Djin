#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include "RenderComponent.h"
#include "MazeComponent.h"

class TankControllerBase;
class GunComponent;
class TankComponent final : public dae::Component
{
public:
	class GameObject;
	TankComponent(dae::GameObject* pGo, MazeComponent* maze, dae::RenderComponent* renderer, TankControllerBase* controller, GunComponent* gun = nullptr);
	~TankComponent();

	void Update() override;
	void FixedUpdate() override;
	void Render() const override;

	void AddMovementInput(glm::ivec2 movement);
	void AddGunRotation(int dir);
	void Shoot();

private:

	float m_Speed = 50.f;
	MazeComponent* m_Maze;
	dae::RenderComponent* m_Renderer;

	TankControllerBase* m_pTankController;

	Direction m_CurrentMovement{};
	glm::ivec2 m_MovementInput;

	//data used to navigate the maze
	Connection* m_pCurrentConnection{ nullptr };
	NodeComponent* m_pCurrentNode;

	GunComponent* m_pGunComponent;

	void ArrivedAtNode(NodeComponent* node);
};

