#pragma once
#include <steam_api.h>
#include "PeterObserver.h"

#define _ACH_ID( id, name ) { id, #id, name, "", 0, 0 }
struct Achievement_t
{
	int m_eAchievementID;
	const char* m_pchAchievementID;
	char m_rgchName[128];
	char m_rgchDescription[256];
	bool m_bAchieved;
	int m_iIconImage;
};


enum EAchievements
{
	ACH_WIN_ONE_GAME = 0,
	ACH_WIN_100_GAMES = 1,
	ACH_TRAVEL_FAR_ACCUM = 2,
	ACH_TRAVEL_FAR_SINGLE = 3,
};



class CSteamAchievements
{
private:
	int64 m_iAppID; // Our current AppID
	Achievement_t* m_pAchievements; // Achievements data
	int m_iNumAchievements; // The number of Achievements
	bool m_bInitialized; // Have we called Request stats and received the callback?


	static CSteamAchievements* instance;
	CSteamAchievements(Achievement_t* Achievements, int NumAchievements);

public:
	~CSteamAchievements() = default;

	static CSteamAchievements* GetInstance()
	{
		if (instance == nullptr)
		{
			Achievement_t g_Achievements[] =
			{
				_ACH_ID(ACH_WIN_ONE_GAME, "Winner"),
				_ACH_ID(ACH_WIN_100_GAMES, "Champion"),
				_ACH_ID(ACH_TRAVEL_FAR_ACCUM, "Interstellar"),
				_ACH_ID(ACH_TRAVEL_FAR_SINGLE, "Orbiter"),
			};

			instance = new CSteamAchievements(g_Achievements, 4);

			return instance;
		}
		else
		return instance;
	}

	bool RequestStats();
	bool SetAchievement(const char* ID);

	STEAM_CALLBACK(CSteamAchievements, OnUserStatsReceived, UserStatsReceived_t,
		m_CallbackUserStatsReceived);
	STEAM_CALLBACK(CSteamAchievements, OnUserStatsStored, UserStatsStored_t,
		m_CallbackUserStatsStored);
	STEAM_CALLBACK(CSteamAchievements, OnAchievementStored,
		UserAchievementStored_t, m_CallbackAchievementStored);
};

