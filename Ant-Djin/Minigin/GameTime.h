#pragma once
#include "Singleton.h"
#include <chrono>

namespace dae
{
	class Time : public Singleton<Time>
	{
	public:
		
		void Init(float fixedTimeStep);
		void ProcessTime();
		float GetElapsed() { return m_DeltaTime; }
		float GetTotal() { return m_AccumulatedTime; }
		float GetFixedTimeStep() { return m_FixedTimeStep; }

	private:

		float m_DeltaTime;
		float m_AccumulatedTime;

		std::chrono::steady_clock::time_point m_CurrentTimePoint;
		std::chrono::steady_clock::time_point m_LastTimePoint;
		float m_FixedTimeStep = .016f; //standard value of 16 ms

	};
}
