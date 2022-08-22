#pragma once
#include "Singleton.h"
#include "TankObserver.h"
#include <Component.h>
class PlayerPointsRecord : public TankObserver, public dae::Singleton<PlayerPointsRecord>
{
public:

	virtual void EnemyKilled(TankType type, TankType killedBy) override;
	int GetPointsP1();
	int GetPointsP2();

	void WriteScoreToFileP1(const std::string& file);
	std::vector<int> ReadScoresFromFile(const std::string& file);

	void ResetScores();

private: 
	friend dae::Singleton<PlayerPointsRecord>;
	PlayerPointsRecord() = default;
	int m_PointsP1;
	int m_PointsP2;
};



