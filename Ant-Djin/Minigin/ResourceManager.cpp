#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

void dae::ResourceManager::Init(const std::string& dataPath)
{
	m_DataPath = dataPath;

	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) 
	{
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) 
	{
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	}

	if (TTF_Init() != 0) 
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

dae::ResourceManager::~ResourceManager()
{
	CleanUpTextures();
	CleanUpFonts();
}

void dae::ResourceManager::CleanUpTextures()
{
	for (auto& texturePair : m_pTextures)
	{
		delete texturePair.second;
	}
}

void dae::ResourceManager::CleanUpFonts()
{
	for (auto& fontPair : m_pFonts)
	{
		delete fontPair.second;
	}
}

dae::Texture2D* dae::ResourceManager::LoadTexture(const std::string& file)
{
	//if the texture allready exists in the map of textures, return it
	auto it = m_pTextures.find(file);
	if (it != m_pTextures.end())
		return it->second;
	

	//load the texture
	const auto fullPath = m_DataPath + file;
	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}

	//add the texture to the map and return it
	dae::Texture2D* tex2D{ new Texture2D(texture) };
	m_pTextures.insert({ file, tex2D });
	return tex2D;
}

dae::Font* dae::ResourceManager::LoadFont(const std::string& file, unsigned int size) 
{
	std::string fontCodeName{ file + std::to_string(size) };
	auto it = m_pFonts.find(fontCodeName);
	if (it != m_pFonts.end())
		return it->second;

	Font* pFont = new Font(m_DataPath + file, size);
	m_pFonts.insert({ fontCodeName , pFont });

	return pFont;
}
