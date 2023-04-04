#include <iostream>
#include "managers/LevelManager.h"

LevelManager* LevelManager::m_instance = nullptr;

LevelManager* LevelManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new LevelManager();
	}

	return m_instance;
}

LevelManager::LevelManager()
{
	m_level = nullptr;
}

LevelManager::~LevelManager()
{
	if (m_level != nullptr)
	{
		delete m_level;
	}

	if (m_instance != nullptr)
	{
		delete m_instance;
	}
}

Level* LevelManager::LoadLevel(sf::RenderTarget& _target, const Vec2f& _tileSize)
{
	if (m_level != nullptr)
	{
		delete m_level;
	}

	m_level = new Level();
	m_level->RenderLevel(_target, _tileSize);

	return m_level;
}
