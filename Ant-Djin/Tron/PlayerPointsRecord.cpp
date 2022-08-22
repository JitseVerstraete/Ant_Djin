#include "PlayerPointsRecord.h"

void PlayerPointsRecord::EnemyKilled(TankType type, TankType killedBy)
{


	int pointsAdded{};

	switch (type)
	{
	case TankType::Player1:
		pointsAdded += 100;
		break;
	case TankType::Player2:
		pointsAdded += 100;
		break;
	case TankType::Enemy:
		pointsAdded += 100;
		break;
	case TankType::Recognizer:
		pointsAdded += 200;
		break;
	default:
		break;
	}


	if (killedBy == TankType::Player1)
	{
		m_PointsP1 += pointsAdded;
	}
	if (killedBy == TankType::Player2)
	{
		m_PointsP2 += pointsAdded;
	}
}

int PlayerPointsRecord::GetPointsP1()
{
	return m_PointsP1;
}
int PlayerPointsRecord::GetPointsP2()
{
	return m_PointsP2;
}

void PlayerPointsRecord::ResetScores()
{
	m_PointsP1 = 0;
	m_PointsP2 = 0;
}
