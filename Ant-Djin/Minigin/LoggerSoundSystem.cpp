#include "MiniginPCH.h"
#include "LoggerSoundSystem.h"

void LoggerSoundSystem::Play(uint16_t id)
{
	m_ss->Play(id);
	std::cout << "Played sound with id: " << id << std::endl;
}

void LoggerSoundSystem::RegisterSound(uint16_t id, const std::string& filePath)
{
	m_ss->RegisterSound(id, filePath);
	std::cout << "Registered sound with id:  " << id << std::endl;
}
