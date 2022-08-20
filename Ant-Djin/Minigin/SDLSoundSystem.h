#pragma once
#include "SoundSystem.h"
class SDLSoundSystem final: public SoundSystem
{
public:
	SDLSoundSystem();
	~SDLSoundSystem();


	void Play(const std::string& path, int volume, bool looping) override;


private:
	class SDLSoundSystemImpl;
	SDLSoundSystemImpl* m_pImpl;

};
