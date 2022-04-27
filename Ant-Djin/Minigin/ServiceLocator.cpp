#include "MiniginPCH.h"
#include "ServiceLocator.h"

dae::ServiceLocator::ServiceLocator()
	: m_pSoundSystem{ nullptr }
	, m_DefaultSoundSystem{}
{
	m_pSoundSystem = &m_DefaultSoundSystem;
}



void dae::ServiceLocator::Destroy()
{
	delete m_pSoundSystem;
	//delete all other future systems encapsulated under this service locator
}

SoundSystem* dae::ServiceLocator::GetSoundSystem() const
{
	return m_pSoundSystem;
}

void dae::ServiceLocator::RegisterSoundSystem(SoundSystem* pSoundSystem)
{
	m_pSoundSystem = (pSoundSystem == nullptr) ? &m_DefaultSoundSystem : pSoundSystem;
}
