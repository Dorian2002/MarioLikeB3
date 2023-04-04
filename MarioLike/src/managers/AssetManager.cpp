#include "managers/AssetManager.h"

#define ASSETS_PATH "resources/images/"

AssetManager* AssetManager::m_instance = nullptr;
std::unordered_map<std::string, sf::Texture*> AssetManager::m_textures;
std::unordered_map<std::string, sf::Font*> AssetManager::m_fonts;

AssetManager* AssetManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new AssetManager();
	}

	return m_instance;
}

AssetManager::~AssetManager()
{
	for (auto& it : m_textures)
	{
		delete it.second;
	}

	for (auto& it : m_fonts)
	{
		delete it.second;
	}

	if (m_instance != nullptr)
	{
		delete m_instance;
	}
}

bool AssetManager::LoadTexture(const std::string& _fileName, const std::string& _assetId)
{
	sf::Texture* texture = new sf::Texture();
	if (texture->loadFromFile(ASSETS_PATH + _fileName))
	{
		m_textures[_assetId] = texture;
		return true;
	}
	else
	{
		delete texture;
		return false;
	}
}
bool AssetManager::LoadFont(const std::string& _fileName, const std::string& _assetId)
{
	sf::Font* font = new sf::Font();
	if (font->loadFromFile(ASSETS_PATH + _fileName))
	{
		m_fonts[_assetId] = font;
		return true;
	}
	else
	{
		delete font;
		return false;
	}
}

sf::Texture* AssetManager::GetTexture(const std::string& _assetId)
{
	if (m_textures.find(_assetId) != m_textures.end())
	{
		return m_textures.at(_assetId);
	}
	else
	{
		return nullptr;
	}
}

sf::Font* AssetManager::GetFont(const std::string& _assetId)
{
	if (m_fonts.find(_assetId) != m_fonts.end())
	{
		return m_fonts.at(_assetId);
	}
	else
	{
		return nullptr;
	}
}
