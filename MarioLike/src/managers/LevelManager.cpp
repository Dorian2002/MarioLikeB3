#include <iostream>
#include "managers/LevelManager.h"
#include <managers/RenderManager.h>

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

Level* LevelManager::LoadLevel()
{
	if (m_level != nullptr)
	{
		delete m_level;
	}

	m_level = new Level();
	m_level->LoadLevel("resources/levels/1-1.txt","resources/levels/1-1.txt");

	return m_level;
}

void LevelManager::RenderLevel()
{
	RenderManager* renderManager = RenderManager::GetInstance();
	for (std::vector<Entity*> line : m_level->m_map) {
		for (Entity* entity : line) {
			renderManager->AddDrawCall(new DrawCall(entity, 1));
		}
	}
}

Level* LevelManager::GetLevel()
{
	return m_level;
}
