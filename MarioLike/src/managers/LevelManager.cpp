#include <iostream>
#include "managers/LevelManager.h"
#include <managers/RenderManager.h>
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
	m_parallaxSky = new Background({0,0});
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

	if (m_parallaxSky != nullptr)
	{
		delete m_parallaxSky;
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
	m_sky = new Background({ 0,0 });
	m_mainSky = m_sky;
	RenderManager::GetInstance()->AddDrawCall(new DrawCall(m_sky, 2));
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
	bool right = false;
	bool left = false;

	RenderManager* renderManager = RenderManager::GetInstance();
	for (std::vector<Entity*> line : m_level->m_map) {
		for (Entity* entity : line) {
			if (t->GetComponent<Transform>()->m_position.x * 16 >= WINDOW_SIZE / 2 && entity->GetComponent<Transform>() && t->m_lastposition.x <= t->GetComponent<Transform>()->m_position.x)
			{
				entity->GetComponent<Transform>()->m_position.x -= 0.1;
				right = true;
			}
			else if(t->GetComponent<Transform>()->m_position.x * 16 < WINDOW_SIZE / 8 && entity->GetComponent<Transform>() && t->m_lastposition.x > t->GetComponent<Transform>()->m_position.x)
			{
				entity->GetComponent<Transform>()->m_position.x += 0.1;
				left = true;
			}
		}
	}
	if (right)
	{
		t->GetComponent<Transform>()->m_position = t->m_lastposition;
		if (m_mainSky->GetComponent<Transform>()->m_position.x < -0.85)
		{
			m_sky->GetComponent<Transform>()->m_position.x = m_parallaxSky->GetComponent<Transform>()->m_position.x + 0.85;
		}
		else if (m_mainSky->GetComponent<Transform>()->m_position.x < 0)
		{
			m_parallaxSky->GetComponent<Transform>()->m_position.x = m_sky->GetComponent<Transform>()->m_position.x + 0.85;
			std::cout << m_sky->GetComponent<Transform>()->m_position.x << std::endl;
			RenderManager::GetInstance()->AddDrawCall(new DrawCall(m_parallaxSky, 3));
		}
		m_sky->GetComponent<Transform>()->m_position.x -= 0.001;
		m_parallaxSky->GetComponent<Transform>()->m_position.x -= 0.001;
	}
	else if (left)
	{
		t->GetComponent<Transform>()->m_position = t->m_lastposition;
		if (m_mainSky->GetComponent<Transform>()->m_position.x > 0.85)
		{
			m_sky->GetComponent<Transform>()->m_position.x = m_parallaxSky->GetComponent<Transform>()->m_position.x - 0.85;
		}
		else if (m_mainSky->GetComponent<Transform>()->m_position.x > 0)
		{
			m_parallaxSky->GetComponent<Transform>()->m_position.x = m_sky->GetComponent<Transform>()->m_position.x - 0.85;
			std::cout << m_sky->GetComponent<Transform>()->m_position.x << std::endl;
			RenderManager::GetInstance()->AddDrawCall(new DrawCall(m_parallaxSky, 3));
		}
		m_sky->GetComponent<Transform>()->m_position.x += 0.001;
		m_parallaxSky->GetComponent<Transform>()->m_position.x += 0.001;
	}

}
