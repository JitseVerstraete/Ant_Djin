#include "MiniginPCH.h"
#include "AchievementSystem.h"
#include "SteamAchievements.h"

void AchievementSystem::GainedPoints(int totalPoints)
{
	if (totalPoints >= 500)
	{

		CSteamAchievements* temp = CSteamAchievements::GetInstance();
		temp->SetAchievement("ACH_WIN_ONE_GAME");

	}
}


AchievementSystem::AchievementSystem()
{

}
