#pragma once
class SoundSystem
{
public: 
	
	virtual ~SoundSystem() = default;
	virtual void Play(std::string path, int volume, bool looping) = 0;

private:


};
