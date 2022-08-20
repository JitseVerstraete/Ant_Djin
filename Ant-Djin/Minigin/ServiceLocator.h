#pragma once
#include "Singleton.h"

#include "SoundSystem.h"
#include "DefaultSoundSystem.h"

namespace dae
{

	class ServiceLocator final : public Singleton<ServiceLocator>
	{
	public:


		void Destroy();

		SoundSystem* GetSoundSystem() const;
		void RegisterSoundSystem(SoundSystem* pSoundSystem);

	private:
		friend Singleton<ServiceLocator>;
		ServiceLocator();
		SoundSystem* m_pSoundSystem = nullptr;
		DefaultSoundSystem m_DefaultSoundSystem{};
	};

}