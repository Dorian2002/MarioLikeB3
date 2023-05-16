#include "engine/GameEngine.h"
#include "utils/Sling.h"
#include "managers/EntityManager.h"
#include "managers/LevelManager.h"

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
	m_window = new sf::RenderWindow(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Suuuuupair maria brasse");
	m_view = new sf::View(sf::FloatRect(0.f, 0.f, WINDOW_SIZE, WINDOW_SIZE));
	m_window->setView(*m_view);
	m_levelManager = LevelManager::GetInstance();
	m_levelManager->LoadLevel();
	m_levelManager->RenderLevel();
	m_entityManager = EntityManager::GetInstance();
	m_entityManager->Start();
	m_renderManager = RenderManager::GetInstance();
	m_renderManager->RenderLevel(*m_window);
	m_inputManager = InputManager::GetInstance();
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

bool GameEngine::Run()
{
	Start();
	while(m_window->isOpen())
	{
		HandleInput();
		ResetTime();
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
	success &= assetManager->LoadTexture("Sky.png", "Background");

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
