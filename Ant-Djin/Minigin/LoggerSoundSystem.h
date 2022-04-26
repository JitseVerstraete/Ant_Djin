#pragma once
#include "SoundSystem.h"
class LoggerSoundSystem : public SoundSystem
{

	SoundSystem* m_ss;
public:
	LoggerSoundSystem(SoundSystem* ss): m_ss{ss} {}
	

	void Play(uint16_t id) override;
	void RegisterSound(uint16_t id, const std::string& filePath);

private:


};

