#include <iostream>
#include "managers/LevelManager.h"
#include <managers/RenderManager.h>
#include <models/Background.h>
#include <managers/EntityManager.h>
#include <engine/GameEngine.h>

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
	m_level->LoadBackground();

	return m_level;
}

void LevelManager::RenderLevel()
{
	RenderManager* renderManager = RenderManager::GetInstance();
	Background* Sky = new Background({ 0,0 });
	RenderManager::GetInstance()->AddDrawCall(new DrawCall(Sky, 1));
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

void LevelManager::MoveLevel()
{
	auto t = EntityManager::GetInstance()->m_toto;
	bool ok = false;


	RenderManager* renderManager = RenderManager::GetInstance();
	for (std::vector<Entity*> line : m_level->m_map) {
		for (Entity* entity : line) {
			if (t->GetComponent<Transform>()->m_position.x * 16 >= WINDOW_SIZE / 2 && entity->GetComponent<Transform>() && t->m_lastposition.x <= t->GetComponent<Transform>()->m_position.x)
			{
				entity->GetComponent<Transform>()->m_position.x -= 0.1;
				ok = true;
			}
			else if(t->GetComponent<Transform>()->m_position.x * 16 < WINDOW_SIZE / 2 && entity->GetComponent<Transform>() && t->m_lastposition.x > t->GetComponent<Transform>()->m_position.x)
			{
				entity->GetComponent<Transform>()->m_position.x += 0.1;
				ok = true;
			}
		}
	}
	if(ok)
		t->GetComponent<Transform>()->m_position = t->m_lastposition;
}
