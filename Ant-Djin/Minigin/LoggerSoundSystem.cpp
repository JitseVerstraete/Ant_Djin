#include "MiniginPCH.h"
#include "LoggerSoundSystem.h"


void LoggerSoundSystem::Play(std::string path, int volume, bool looping)
{
	m_ss->Play(path, volume, looping);
	std::cout << "LOGGER SOUND SYSTEM: Called Play on sound with path: " << path << std::endl;
}

