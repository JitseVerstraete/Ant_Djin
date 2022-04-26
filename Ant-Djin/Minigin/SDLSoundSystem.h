#pragma once
#include "SoundSystem.h"
class SDLSoundSystem : public SoundSystem
{
public:
	SDLSoundSystem();
	~SDLSoundSystem();


	void Play(uint16_t id, float volume);
	void RegisterSound(uint16_t id, const std::string& filePath);

private:
	class SDLSoundSystemImpl;
	SDLSoundSystemImpl* m_pImpl;

};
