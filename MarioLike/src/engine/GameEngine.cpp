#include "engine/GameEngine.h"
#include "utils/Sling.h"
#include <models/toto.h>
#include <managers/AssetManager.h>

GameEngine* GameEngine::m_engine = nullptr;

DECLARE_DELEGATE(FOnUpdate, float);

GameEngine* GameEngine::GetInstance()
{
	if(m_engine == nullptr)
	{
		m_engine = new GameEngine();
	}
	return m_engine;
}

GameEngine::~GameEngine()
{
	delete m_engine;
}
void GameEngine::Start()
{
	LoadResources();
	m_window = new sf::RenderWindow(sf::VideoMode(500, 500), "Suuuuupair maria brasse");
	m_levelManager = LevelManager::GetInstance();
	m_levelManager->LoadLevel();
	m_levelManager->RenderLevel();
	m_entityManager = EntityManager::GetInstance();
	m_entityManager->Start();
	m_renderManager = RenderManager::GetInstance();
	m_renderManager->RenderLevel(*m_window);
}

void GameEngine::Update()
{
	m_entityManager->Update();
}

void GameEngine::Render()
{
	m_window->clear();
	//m_level->LoadLevel(*m_window, { 16,16 });
	m_renderManager->RenderLevel(*m_window);
	m_window->display();
}

bool GameEngine::Run()
{
	Start();
	while(m_window->isOpen())
	{
		sf::Event e;
		while (m_window->pollEvent(e)) {
			switch (e.type)
			{
			case sf::Event::Closed:
				m_window->close();
				break;
			case sf::Event::KeyPressed:
				switch (e.key.alt) {
				case sf::Keyboard::Right:
					break;
				case sf::Keyboard::Left:
					break;
				}
				break;
			default:
				break;
			}
		}
		Update();
		Render();
		ResetTime();
	}
	return true;
}

sf::RenderWindow* GameEngine::GetWindow()
{
	return m_window;
}


float GameEngine::GetDeltaTime()
{
	return m_clock.getElapsedTime().asSeconds();
}

void GameEngine::ResetTime()
{
	m_clock.restart();
}

bool GameEngine::LoadResources()
{
	bool success = true;
	AssetManager* assetManager = AssetManager::GetInstance();

	success &= assetManager->LoadTexture("PetitMario.png", "petitMario");
	success &= assetManager->LoadTexture("Block.png", "block");

	//success &= assetManager->LoadTexture("map_assets/brick.png", "brick");
	//success &= assetManager->LoadTexture("map_assets/wall.png", "wall");
	//success &= assetManager->LoadTexture("map_assets/grass.png", "grass");
	//success &= assetManager->LoadTexture("mc_animations/F1.png", "F1");
	//success &= assetManager->LoadTexture("map_assets/opened_trap.png", "o_trap");
	//success &= assetManager->LoadTexture("map_assets/closed_trap.png", "c_trap");
	//success &= assetManager->LoadTexture("bomb_animations/B1.png", "B1");

	if (success)
	{
		std::cout << ">> Loading resources was successful !" << std::endl;
	}
	else
	{
		std::cout << ">> Error while loading resources !" << std::endl;
		return false;
	}

	return true;
}
