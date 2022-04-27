#pragma once
#include "SoundSystem.h"

//empty sound system (does nothing, but is used as a fallback if no sound system in registered in service locator)
class DefaultSoundSystem final : public SoundSystem
{
public:
	DefaultSoundSystem() = default;
	~DefaultSoundSystem() = default;


	void Play(std::string , int , bool ) override {};

private:
};
