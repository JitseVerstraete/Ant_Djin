#pragma once
#include "SoundSystem.h"
class SDLSoundSystem : public SoundSystem
{

	SoundSystem* m_ss;
public:
	SDLSoundSystem(SoundSystem* ss) : m_ss{ ss } {}


	void Play(uint16_t id, float volume);
	void RegisterSound(uint16_t id, const std::string& filePath);

private:


};
