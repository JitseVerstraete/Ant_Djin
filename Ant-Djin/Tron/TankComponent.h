#pragma once
#include "Component.h"



class MazeComponent;
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

};

