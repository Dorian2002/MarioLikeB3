#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <unordered_map>

class AssetManager
{
public:
	virtual ~AssetManager();
	AssetManager(const AssetManager& _other) = delete;
	void operator=(const AssetManager& _other) = delete;
	static AssetManager* GetInstance();

	bool LoadTexture(const std::string& _fileName, const std::string& _assetId);
	bool LoadFont(const std::string& _fileName, const std::string& _assetId);
	sf::Texture* GetTexture(const std::string& _assetId);
	sf::Font* GetFont(const std::string& _assetId);

private:
	AssetManager() = default;
	static AssetManager* m_instance;

	static std::unordered_map<std::string, sf::Texture*> m_textures;
	static std::unordered_map<std::string, sf::Font*> m_fonts;
};

