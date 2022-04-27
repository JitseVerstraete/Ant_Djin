#pragma once
class SoundSystem
{
public: 

	virtual void Play(std::string path, int volume, bool looping) = 0;

private:


};
