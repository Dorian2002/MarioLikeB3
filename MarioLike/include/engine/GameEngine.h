#pragma once
#include "SFML/Graphics.hpp"
#include "models/Level.h"
#include "managers/LevelManager.h"
#include "managers/EntityManager.h"
#include <managers/RenderManager.h>
#include "managers/InputManager.h"
#include <chrono>
class GameEngine
{
public:
	virtual ~GameEngine();
	GameEngine(const GameEngine& _other) = delete;
	void operator =(const GameEngine& _other) = delete;
	static GameEngine* GetInstance();
	bool Run();
	int m_frames = 0;
	sf::RenderWindow* GetWindow();
	float GetDeltaTime();
	const std::chrono::nanoseconds FRAMETIME = std::chrono::nanoseconds(16666667);;
private:
	GameEngine() = default;
	void Start();
	void HandleInput();
	void Update();
	void Render();
	bool LoadResources();
	static GameEngine* m_engine;
	sf::Clock m_clock;
	void ResetTime();
	sf::RenderWindow* m_window;
	LevelManager* m_levelManager;
	EntityManager* m_entityManager;
	RenderManager* m_renderManager;
	InputManager* m_inputManager;
};
