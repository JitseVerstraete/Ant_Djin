#include "MiniginPCH.h"
#include "SDLSoundSystem.h"

void SDLSoundSystem::Play(uint16_t id, float volume)
{
	m_ss->Play(id, volume);
	//play audio clip
}

void SDLSoundSystem::RegisterSound(uint16_t id, const std::string& filePath)
{
	m_ss->RegisterSound(id, filePath);
	//register sound
}
