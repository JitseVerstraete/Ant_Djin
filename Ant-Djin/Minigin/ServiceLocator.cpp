#include "MiniginPCH.h"
#include "ServiceLocator.h"

SoundSystem* dae::ServiceLocator::GetSoundSystem() const
{
	return m_pSoundSystem;
}
