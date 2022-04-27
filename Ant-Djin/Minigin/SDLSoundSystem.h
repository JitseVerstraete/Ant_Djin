#pragma once
#include "SoundSystem.h"
class SDLSoundSystem : public SoundSystem
{
public:
	SDLSoundSystem();
	~SDLSoundSystem();


	void Play(std::string path, int volume, bool looping) override;


private:
	class SDLSoundSystemImpl;
	SDLSoundSystemImpl* m_pImpl;

};
