#pragma once
#include "GameScene.h"  
#include "TankComponent.h"


class TronScene : public dae::GameScene
{
public:
	TronScene(int startLives) :GameScene("tronScene"), m_playerSTartLives{startLives} {}

protected:

	void Initialize() override;

	void SceneUpdate() override;

private:
	int m_playerSTartLives;

	TankComponent* m_PlayerTank;
};


