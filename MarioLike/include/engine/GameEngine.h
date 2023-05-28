#pragma once

#include "SFML/Graphics.hpp"
#include <chrono>
#include <models/Menu.h>
#include "models/UIGameLevel.h"

#define WINDOW_SIZE 500

class LevelManager;
class EntityManager;
class RenderManager;
class InputManager;

class GameEngine
{
public:
	virtual ~GameEngine();
	GameEngine(const GameEngine& _other) = delete;
	void operator =(const GameEngine& _other) = delete;
	static GameEngine* GetInstance();
	bool RunGame();
	bool RunMenu();
	void BackToMenu();
	int m_frames = 0;
	sf::RenderWindow* GetWindow();
	float GetDeltaTime();
	float deltatime = 0.0f;	
private:
	GameEngine() = default;
	void Start();
	void HandleInput();
	void Update();
	void Render();
	bool LoadResources();
	bool LoadMenuResources();
	static GameEngine* m_engine;
	sf::Clock m_clock;
	void ResetTime();
	sf::RenderWindow* m_window;
	LevelManager* m_levelManager;
	EntityManager* m_entityManager;
	RenderManager* m_renderManager;
	InputManager* m_inputManager;
	Menu* m_Menu;
	UIGameLevel* m_gameUI;
};
