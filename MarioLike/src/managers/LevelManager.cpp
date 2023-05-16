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

//Function that Load the level structure from text file
Level* LevelManager::LoadLevel()
{
	//if m_level is not null, delete it
	if (m_level != nullptr)
	{
		delete m_level;
	}

	//Create new level and loadLevel from text file
	m_level = new Level();
	m_level->LoadLevel("resources/levels/1-1.txt","resources/levels/1-1.txt");
	return m_level;
}

//Function that display the level element according to the m_map vector
void LevelManager::RenderLevel()
{
	//Get renderManager
	RenderManager* renderManager = RenderManager::GetInstance();

	//Create Background, define it as the main background and display it via drawCall
	m_sky = new Background({ 0,0 });
	m_mainSky = m_sky;
	RenderManager::GetInstance()->AddDrawCall(new DrawCall(m_sky, 2));

	//iterate over the m_map vector to render each element via drawCall
	for (std::vector<Entity*> line : m_level->m_map) {
		for (Entity* entity : line) {
			renderManager->AddDrawCall(new DrawCall(entity, 1));
		}
	}
}

//m_level getter
Level* LevelManager::GetLevel()
{
	return m_level;
}

//Function that move the level and handdle parallax
void LevelManager::MoveLevel()
{
	//We get the player in the EntityManager
	auto t = EntityManager::GetInstance()->m_toto;
	bool right = false;
	bool left = false;

	//Get render manager
	RenderManager* renderManager = RenderManager::GetInstance();

	//For each element in the map
	for (std::vector<Entity*> line : m_level->m_map) {
		for (Entity* entity : line) {

			//If player position is milddle screen an dplayer go to the right
			if (t->GetComponent<Transform>()->m_position.x * 16 >= WINDOW_SIZE / 2 && entity->GetComponent<Transform>() && t->m_lastposition.x <= t->GetComponent<Transform>()->m_position.x)
			{
				//Move the map to the right
				entity->GetComponent<Transform>()->m_position.x -= 0.1;
				right = true;
			}

			//If player position is 1/4 screen and go to the left
			else if(t->GetComponent<Transform>()->m_position.x * 16 < WINDOW_SIZE / 8 && entity->GetComponent<Transform>() && t->m_lastposition.x > t->GetComponent<Transform>()->m_position.x)
			{
				//Move the map to the left
				entity->GetComponent<Transform>()->m_position.x += 0.1;
				left = true;
			}
		}
	}

	//If the level move to the right
	if (right)
	{
		//lock player in middle screen position
		t->GetComponent<Transform>()->m_position = t->m_lastposition;

		//If the main background not cover entirely cicle with the other background
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

		//Move the backgrounds
		m_sky->GetComponent<Transform>()->m_position.x -= 0.001;
		m_parallaxSky->GetComponent<Transform>()->m_position.x -= 0.001;
	}
	else if (left)
	{
		//lock player in 1/4 screen position
		t->GetComponent<Transform>()->m_position = t->m_lastposition;

		//If the main background not cover entirely cicle with the other background
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

		//Move the backgrounds
		m_sky->GetComponent<Transform>()->m_position.x += 0.001;
		m_parallaxSky->GetComponent<Transform>()->m_position.x += 0.001;
	}

}
