#include "PlayerPointsRecord.h"
#include <fstream>
#include <iostream>
#include <algorithm>

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

void PlayerPointsRecord::WriteScoreToFileP1(const std::string& file)
{
	
	auto scores = ReadScoresFromFile(file);

	std::sort(scores.begin(), scores.end(), [](int i, int j) { return i > j; });

	scores.push_back(m_PointsP1);

	std::ofstream outputScores(file);

	for (auto score : scores)
	{
		outputScores << score << std::endl;
	}
	outputScores.close();




}

std::vector<int> PlayerPointsRecord::ReadScoresFromFile(const std::string& file)
{
	std::vector<int> scores{};


	std::ifstream highScores(file);
	if (highScores)
	{
		while (!highScores.eof())
		{
			int score{};
			highScores >> score;
			scores.push_back(score);
		}
	}
	highScores.close();

	return scores;
}

void PlayerPointsRecord::ResetScores()
{
	m_PointsP1 = 0;
	m_PointsP2 = 0;
}
