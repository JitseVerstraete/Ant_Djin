#include "MiniginPCH.h"
#include "Time.h"

using namespace std::chrono;

void dae::Time::Init(float fixedTimeStep)
{
	m_LastTimePoint = high_resolution_clock::now();
	m_AccumulatedTime = 0.f;
	m_FixedTimeStep = fixedTimeStep;
}

void dae::Time::ProcessTime()
{
	m_CurrentTimePoint = high_resolution_clock::now();
	m_DeltaTime = duration<float>(m_CurrentTimePoint - m_LastTimePoint).count();
	m_AccumulatedTime += m_DeltaTime;
	m_LastTimePoint = m_CurrentTimePoint;
}
