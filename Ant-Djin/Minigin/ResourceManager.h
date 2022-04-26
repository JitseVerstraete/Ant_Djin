#pragma once
#include "Singleton.h"
#include <map>

namespace dae
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& dataPath);
		~ResourceManager();

		void CleanUpTextures();
		void CleanUpFonts();

		Texture2D* LoadTexture(const std::string& file);
		Font* LoadFont(const std::string& file, unsigned int size);
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_DataPath;
		
		std::map<std::string, Texture2D*> m_pTextures{};
		std::map<std::string, Font*> m_pFonts{};
		
	};
}
