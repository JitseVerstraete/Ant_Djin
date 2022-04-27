#pragma once
#include "SoundSystem.h"
class LoggerSoundSystem : public SoundSystem
{

	SoundSystem* m_ss;
public:
	LoggerSoundSystem(SoundSystem* ss): m_ss{ss} {}
	
	void Play(std::string path, int volume, bool looping) override;

private:


};

