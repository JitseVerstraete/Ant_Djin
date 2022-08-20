#include "MiniginPCH.h"
#include "SDLSoundSystem.h"

#include "SDL_mixer.h"

#include <map>
#include <queue>
#include <condition_variable>
#include <thread>
#include <mutex>

//todo: loading and playing on a different threads with event queue
//todo: make the sound system a service (service loacator)

struct PlayRequest
{
	std::string path;
	int volume;
	bool looping;
};

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

		if (IsLoaded())
			Mix_FreeChunk(m_pChunk);

	}

	bool Load()
	{
		if (IsLoaded()) return true;

		m_pChunk = Mix_LoadWAV(m_Path.c_str());
		if (m_pChunk == nullptr)
		{
			std::cerr << "audioclip " << m_Path << " failed to load, SDL_mixer error: " << Mix_GetError() << std::endl;
			return false;
		}
		return true;
	}

	bool Play(int volume, bool looping)
	{
		if (!IsLoaded()) return false;

		SetVolume(volume);
		int loops = looping ? -1 : 0;

		int channel{ Mix_PlayChannel(-1, m_pChunk, loops) };
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
		: m_Thread{ std::jthread(&SDLSoundSystemImpl::HandlePlayRequests, this) }
		, m_Quitting{ false }
	{
		int result = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

		if (result != 0)
		{
			std::cout << "Failed to open audio: " << Mix_GetError() << std::endl;
		}

		Mix_AllocateChannels(32);
	}

	~SDLSoundSystemImpl()
	{
		for (auto clipPair : m_Clips)
		{
			delete clipPair.second;
		}

		m_Quitting = true;
		m_Cv.notify_all();
		Mix_CloseAudio();
	}


	void Play(const std::string& path, int volume, bool loop)
	{

		PlayRequest request{ path, volume, loop };
		std::unique_lock lock{ m_Mutex };
		m_Requests.emplace(PlayRequest(path, volume, loop));
		m_Cv.notify_one();
	}



private:
	std::map<std::string, SDLSoundClip*> m_Clips{};
	std::queue<PlayRequest> m_Requests{};
	std::condition_variable m_Cv{};
	std::mutex m_Mutex{};
	std::jthread m_Thread;
	bool m_Quitting{ false };


	//private functions
	void HandlePlayRequests()
	{
		while (!m_Quitting)
		{
			std::unique_lock lk{ m_Mutex };

			if (m_Requests.size() > 0)
			{
				PlayRequest request = m_Requests.front();
				m_Requests.pop();

				lk.unlock();

				LoadAndPlaySound(request);
			}
			else
			{
				m_Cv.wait(lk);
			}
		}
	}


	void LoadAndPlaySound(PlayRequest request)
	{
		auto foundClip = m_Clips.find(request.path);
		if (foundClip != m_Clips.end())
		{
			foundClip->second->Play(request.volume, request.looping);
		}
		else
		{
			SDLSoundClip* pClip{ new SDLSoundClip(request.path) };
			if (pClip->Load())
			{
				pClip->Play(request.volume, request.looping);
				m_Clips.insert({ request.path, pClip });
			}
		}



	}



};



SDLSoundSystem::SDLSoundSystem()
{
	m_pImpl = new SDLSoundSystemImpl();
}

SDLSoundSystem::~SDLSoundSystem()
{
	delete m_pImpl;
}

void SDLSoundSystem::Play(const std::string& path, int volume, bool looping)
{
	m_pImpl->Play(path, volume, looping);
}

