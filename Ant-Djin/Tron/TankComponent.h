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

enum class TankType
{
	Player1,
	Player2,
	Enemy,
	Recognizer
};


class TankObserver;
class TankControllerBase;
class GunComponent;
class TankComponent final : public dae::Component
{
public:
	class GameObject;
	TankComponent(dae::GameObject* pGo, MazeComponent* maze, NodeComponent* spawnNode, dae::RenderComponent* renderer, TankControllerBase* controller, Team team, TankType type, float speed, int lives );
	~TankComponent();

	void Update() override;
	void FixedUpdate() override;
	void Render() const override;

	void OnCollision(dae::GameObject* other, dae::CollisionType type) override;

	void AddObserver(TankObserver* observer);

	void SetGun(GunComponent* gun);

	void AddMovementInput(glm::ivec2 movement);
	void AddGunRotation(int dir);
	void Shoot();

	int GetLives() { return m_Lives; }
	

	Team GetTeam() { return m_Team; }
	TankType GetType() { return m_Type; }

	const std::vector<TankObserver*>& GetObservers();

	static const std::vector<TankComponent*>& GetAllTanks() { return m_AllTanks; }
	static std::vector<TankComponent*> GetPlayerTanks();
	static std::vector<TankComponent*> GetEnemyTanks();

	Direction GetMovementDir() { return m_CurrentMovement; }

private:

	float m_Speed = 50.f;
	MazeComponent* m_Maze;
	dae::RenderComponent* m_Renderer;

	int m_Lives;

	TankControllerBase* m_pTankController;

	Direction m_CurrentMovement{};
	glm::ivec2 m_MovementInput;

	//data used to navigate the maze
	Connection* m_pCurrentConnection{ nullptr };
	NodeComponent* m_pCurrentNode;

	GunComponent* m_pGunComponent;

	Team m_Team;
	TankType m_Type;


	std::vector<TankObserver*> m_Observers;

	static std::vector<TankComponent*> m_AllTanks;

	void ArrivedAtNode(NodeComponent* node);
};

