#include "MiniginPCH.h"
#include "GameTime.h"

using namespace std::chrono;

void dae::GameTime::Init(float fixedTimeStep)
{
	m_LastTimePoint = high_resolution_clock::now();
	m_AccumulatedTime = 0.f;
	m_FixedTimeStep = fixedTimeStep;
}

void dae::GameTime::ProcessTime()
{
	m_CurrentTimePoint = high_resolution_clock::now();
	m_DeltaTime = duration<float>(m_CurrentTimePoint - m_LastTimePoint).count();
	m_AccumulatedTime += m_DeltaTime;
	m_LastTimePoint = m_CurrentTimePoint;
}
