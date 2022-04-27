#pragma once
#include "Singleton.h"

#include "SoundSystem.h"
#include "DefaultSoundSystem.h"

namespace dae
{

	class ServiceLocator : public Singleton<ServiceLocator>
	{
	public:
		SoundSystem* GetSoundSystem() const;
		void RegisterSoundSystem(SoundSystem* pSoundSystem);

	private:
		friend Singleton<ServiceLocator>;
		SoundSystem* m_pSoundSystem = nullptr;
		DefaultSoundSystem m_DefaultSoundSystem{};
	};

}