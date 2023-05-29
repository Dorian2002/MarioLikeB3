#include <iostream>
#include "managers/LevelManager.h"
#include <managers/RenderManager.h>
#include <managers/EntityManager.h>
#include <engine/GameEngine.h>
class Player;

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
		m_level = nullptr;
	}
	if (m_parallaxSky != nullptr)
	{
		delete m_parallaxSky;
		m_parallaxSky = nullptr;
	}
	if (m_sky != nullptr)
	{
		delete m_sky;
		m_sky = nullptr;
	}
	m_instance = nullptr;
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
	m_parallaxSky = new Background({ 1,0});
	RenderManager::GetInstance()->AddDrawCall(new DrawCall(m_sky, 2));
	RenderManager::GetInstance()->AddDrawCall(new DrawCall(m_parallaxSky, 2));
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
	auto player = EntityManager::GetInstance()->m_player;
	auto cameraView = GameEngine::GetInstance()->GetWindow();
	sf::View currentView = cameraView->getView();
	bool right = false;
	bool left = false;

	//Get render manager
	RenderManager* renderManager = RenderManager::GetInstance();
	auto velX = player->GetComponent<PhysicsComponent>()->m_velocity.x;
	auto posX = player->GetComponent<Transform>()->m_position.x;
	//If player position is milddle screen an dplayer go to the right
	float centerX = currentView.getCenter().x;
	float offset = 0.f;
	if (posX * 16 >= currentView.getCenter().x && player->IsWalking() && velX > 0)
	{
		//Move the map to the right
		offset = posX * 16 - currentView.getCenter().x;
		right = true;
	}
	else if (posX * 16 <= currentView.getCenter().x && player->IsWalking() && velX < 0)
	{
		//Move the map to the left
		offset = posX * 16 - currentView.getCenter().x;
		left = true;
	}

	centerX = std::clamp(centerX + offset, currentView.getSize().x * 0.5f, m_level->m_levelSize * 16 - currentView.getSize().x * 0.5f);
	if (currentView.getCenter().x == centerX)
	{
		left = false;
		right = false;
	}
	currentView.setCenter({ centerX, currentView.getCenter().y });

	cameraView->setView(currentView);

	//If the level move to the right
	if (right)
	{
		//If the main background not cover entirely cycle with the other background
		if (m_sky->GetComponent<SpriteComponent>()->m_sprite->getPosition().x + m_parallaxSky->GetComponent<SpriteComponent>()->m_spriteSize.x <= currentView.getCenter().x - currentView.getSize().x / 2)
			m_sky->GetComponent<Transform>()->m_position.x = m_parallaxSky->GetComponent<Transform>()->m_position.x + 0.999f;

		else if (m_sky->GetComponent<SpriteComponent>()->m_sprite->getPosition().x + m_sky->GetComponent<SpriteComponent>()->m_spriteSize.x <= currentView.getCenter().x + currentView.getSize().x / 2)
			m_parallaxSky->GetComponent<Transform>()->m_position.x = m_sky->GetComponent<Transform>()->m_position.x + 0.999f;

		//Move the backgrounds
		m_sky->GetComponent<Transform>()->m_position.x -= 0.0001;
		m_parallaxSky->GetComponent<Transform>()->m_position.x -= 0.0001;
	}
	else if (left)
	{

		//If the main background not cover entirely cycle with the other background
		if (m_sky->GetComponent<SpriteComponent>()->m_sprite->getPosition().x >= currentView.getCenter().x + currentView.getSize().x / 2)
			m_sky->GetComponent<Transform>()->m_position.x = m_parallaxSky->GetComponent<Transform>()->m_position.x - 0.999;

		else if (m_sky->GetComponent<SpriteComponent>()->m_sprite->getPosition().x >= currentView.getCenter().x - currentView.getSize().x / 2)
			m_parallaxSky->GetComponent<Transform>()->m_position.x = m_sky->GetComponent<Transform>()->m_position.x - 0.999;

		//Move the backgrounds
		m_sky->GetComponent<Transform>()->m_position.x += 0.0001;
		m_parallaxSky->GetComponent<Transform>()->m_position.x += 0.0001;
	}
}
