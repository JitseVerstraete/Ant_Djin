#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include "RenderComponent.h"
#include "MazeComponent.h"

enum class Team
{
	Player,
	Enemy
};

class TankControllerBase;
class GunComponent;
class TankComponent final : public dae::Component
{
public:
	class GameObject;
	TankComponent(dae::GameObject* pGo, MazeComponent* maze, dae::RenderComponent* renderer, TankControllerBase* controller, Team team, float speed, GunComponent* gun = nullptr);
	~TankComponent();

	void Update() override;
	void FixedUpdate() override;
	void Render() const override;

	void SetGun(GunComponent* gun);

	void AddMovementInput(glm::ivec2 movement);
	void AddGunRotation(int dir);
	void Shoot();

	Team GetTeam() { return m_Team; }
	static const std::vector<TankComponent*>& GetAllTanks() { return m_AllTanks; }

	Direction GetMovementDir() { return m_CurrentMovement; }

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

	Team m_Team;

	static std::vector<TankComponent*> m_AllTanks;

	void ArrivedAtNode(NodeComponent* node);
};

