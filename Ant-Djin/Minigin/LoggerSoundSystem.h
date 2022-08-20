#pragma once
#include "SoundSystem.h"
class LoggerSoundSystem final : public SoundSystem
{

	SoundSystem* m_ss;
public:
	LoggerSoundSystem(SoundSystem* ss): m_ss{ss} {}
	~LoggerSoundSystem() { delete m_ss; }
	
	void Play(const std::string& path, int volume, bool looping) override;

private:


};

