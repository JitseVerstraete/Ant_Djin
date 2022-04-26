#include "MiniginPCH.h"
#include "SDLSoundSystem.h"

#include "SDL_mixer.h"

#include <map>
#include <queue>

class SDLSoundClip
{
public:
	SDLSoundClip(const std::string& path)
		: m_Path{ path }
		, m_pChunk{ nullptr }
	{
	}

	~SDLSoundClip()
	{
		/*
		if (IsLoaded())
			Mix_FreeChunk(m_pChunk);
		*/
	}

	void Load()
	{
		m_pChunk = Mix_LoadWAV(m_Path.c_str());
		if (m_pChunk == nullptr)
		{
			std::cerr << "audioclip " << m_Path << " failed to load, SDL_mixer error: " << Mix_GetError() << std::endl;
		}
	}

	bool Play()
	{
		if (!IsLoaded()) return false;

		int channel{ Mix_PlayChannel(-1, m_pChunk, 0) };
		return channel == -1 ? false : true;
	}

	void SetVolume(int volume)
	{
		if (IsLoaded())
			Mix_VolumeChunk(m_pChunk, volume);
	}

	int GetVolume()
	{
		if (IsLoaded())
			return Mix_VolumeChunk(m_pChunk, -1);
	}

	bool IsLoaded()
	{
		return m_pChunk != nullptr;
	}


private:
	std::string m_Path{};
	Mix_Chunk* m_pChunk;

};

class SDLSoundSystem::SDLSoundSystemImpl
{
public:
	SDLSoundSystemImpl()
	{
		int result = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 8, 1024);

		if (result != 0)
		{
			std::cout << "Failed to open audio: " << Mix_GetError() << std::endl;
		}
	}

	~SDLSoundSystemImpl()
	{
		Mix_Quit();
	}


	void Play(uint16_t id)
	{
		auto it = m_Clips.find(id);
		if (it != m_Clips.end())
		{
			if (!it->second.IsLoaded())
			{
				it->second.Load();
			}
			it->second.Play();
		}
		else
		{
			std::cerr << "Sound with id " << id << " was not found!\n";
		}

	}

	void RegisterSound(uint16_t id, const std::string& filePath)
	{
		m_Clips.insert(std::pair<uint16_t, SDLSoundClip>(id, SDLSoundClip(filePath)));
	}


private:
	std::map<uint16_t, SDLSoundClip> m_Clips{};

};



SDLSoundSystem::SDLSoundSystem()
{
	m_pImpl = new SDLSoundSystemImpl();
}

SDLSoundSystem::~SDLSoundSystem()
{
	delete m_pImpl;
}

void SDLSoundSystem::Play(uint16_t id)
{
	m_pImpl->Play(id);
}

void SDLSoundSystem::RegisterSound(uint16_t id, const std::string& filePath)
{
	m_pImpl->RegisterSound(id, filePath);
}