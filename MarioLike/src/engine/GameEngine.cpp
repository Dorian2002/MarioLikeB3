#include "engine/GameEngine.h"
#include "utils/Sling.h"
#include <models/toto.h>

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
	m_window = new sf::RenderWindow(sf::VideoMode(500, 500), "Suuuuupair maria brasse");
}

void GameEngine::Update()
{
}

void GameEngine::Render()
{
	m_window->clear();
	m_window->display();
}

bool GameEngine::Run()
{
	Start();
	//toto* var = new toto();
	//var->Start();
	while(m_window->isOpen())
	{
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
