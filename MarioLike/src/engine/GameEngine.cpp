#include "engine/GameEngine.h"
#include "utils/Sling.h"
#include "managers/AssetManager.h"
#include "managers/EntityManager.h"
#include "managers/LevelManager.h"
#include "utils/Button.h"
#include <SFML/Graphics.hpp>

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
	delete m_window;
	delete m_renderManager;
	delete m_inputManager;
}

void GameEngine::Start()
{
	LoadResources();
	m_levelManager = LevelManager::GetInstance();
	m_levelManager->LoadLevel();
	m_levelManager->RenderLevel();
	m_entityManager = EntityManager::GetInstance();
	m_entityManager->Start();
	m_renderManager = RenderManager::GetInstance();
	m_renderManager->RenderLevel(*m_window);
	m_inputManager = InputManager::GetInstance();
	m_inputManager->AddKeyBind(sf::Keyboard::Escape, new Event::Slot<>(this, &GameEngine::BackToMenu), onKeyPress);
}

void GameEngine::HandleInput()
{
	m_inputManager->HandleInput();
}

void GameEngine::Update()
{
	m_entityManager->Update();
}

void GameEngine::Render()
{
	m_window->clear();
	m_levelManager->MoveLevel();
	m_renderManager->RenderLevel(*m_window);
	m_window->display();
}

bool GameEngine::RunGame()
{
	delete m_Menu;
	m_Menu = nullptr;

	Start();
	
	auto clock = sf::Clock();
	while(m_window->isOpen())
	{
		deltatime = clock.restart().asSeconds();
		HandleInput();
		Update();
		Render();

		//std::cout << GetDeltaTime() << std::endl;

		 //= clock.getElapsedTime().asSeconds() - frameTimeStart;
		//std::cout << "frames per second: " << (float)m_frames / ((float)millisPassed.count() / 1000.f) << std::endl;

	}
	return true;
}



bool GameEngine::RunMenu()
{
	LoadMenuResources();
	if (!m_window)
		m_window = new sf::RenderWindow(sf::VideoMode(960,540), "Suuuuupair maria brasse", sf::Style::Titlebar | sf::Style::Close);
	sf::View currentView = m_window->getView();
	currentView.reset(sf::FloatRect(0, 0, m_window->getSize().x, m_window->getSize().y));
	m_window->setView(currentView);
	m_Menu = new Menu(m_window);

	while (m_window->isOpen())
	{
		m_window->clear();
		sf::Event event;
		while (m_window->pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
			{
				m_window->close();
				return true;
			}
			m_Menu->HandleEvents(&event);
		}
		m_Menu->DrawMenu();
		m_window->display();
	}
	return true;
}

void GameEngine::BackToMenu()
{
	delete m_entityManager;
	m_entityManager = nullptr;
	delete m_levelManager;
	m_levelManager = nullptr;
	delete m_renderManager;
	m_renderManager = nullptr;
	delete m_inputManager;
	m_inputManager = nullptr;
	RunMenu();
}

sf::RenderWindow* GameEngine::GetWindow()
{
	return m_window;
}


float GameEngine::GetDeltaTime()
{
	return deltatime;
}

void GameEngine:: ResetTime()
{
	m_clock.restart();
}

bool GameEngine::LoadResources()
{
	bool success = true;
	AssetManager* assetManager = AssetManager::GetInstance();

	success &= assetManager->LoadTexture("littleMarioRun.png", "littleMarioRun");
	success &= assetManager->LoadTexture("littleMarioIdle.png", "littleMarioIdle");
	success &= assetManager->LoadTexture("BoombaRun.png", "boombaRun");
	success &= assetManager->LoadTexture("BoombaIdle.png", "boombaIdle");
	success &= assetManager->LoadTexture("Block.png", "block");
	success &= assetManager->LoadTexture("coin.png", "coin");
	success &= assetManager->LoadTexture("Sky.png", "Background");
	success &= assetManager->LoadTexture("Finish.png", "finish");

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

bool GameEngine::LoadMenuResources()
{
	bool success = true;
	AssetManager* assetManager = AssetManager::GetInstance();

	success &= assetManager->LoadTexture("menuBackground.jpg", "menuBackground");
	success &= assetManager->LoadFont("SuperMarioBros.ttf", "mainFont");

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
