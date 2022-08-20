#pragma once
#include "Singleton.h"
#include <chrono>

namespace dae
{
	class GameTime final : public Singleton<GameTime>
	{
	public:
		
		void Init(float fixedTimeStep = 0.016f);
		void ProcessTime();
		float GetElapsed() { return m_DeltaTime; }
		float GetTotal() { return m_AccumulatedTime; }
		float GetFixedTimeStep() { return m_FixedTimeStep; }

	private:
		friend Singleton<GameTime>;
		GameTime();

		float m_DeltaTime;
		float m_AccumulatedTime;

		std::chrono::steady_clock::time_point m_CurrentTimePoint;
		std::chrono::steady_clock::time_point m_LastTimePoint;
		float m_FixedTimeStep; 

	};
}
