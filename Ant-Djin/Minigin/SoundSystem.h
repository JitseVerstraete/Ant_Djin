#pragma once
class SoundSystem
{
public: 


	virtual void Play(uint16_t id) = 0;
	virtual void RegisterSound(uint16_t id, const std::string& filePath) = 0;

private:


};

