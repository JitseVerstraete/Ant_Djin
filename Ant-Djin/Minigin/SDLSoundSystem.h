#pragma once
#include "SoundSystem.h"
class SDLSoundSystem : public SoundSystem
{
public:
	SDLSoundSystem();
	~SDLSoundSystem();


	void Play(uint16_t id) override;
	void RegisterSound(uint16_t id, const std::string& filePath) override;
	void SetSoundVolume(int volume);
	void GetSoundVolume(int volume);

private:
	class SDLSoundSystemImpl;
	SDLSoundSystemImpl* m_pImpl;

};
