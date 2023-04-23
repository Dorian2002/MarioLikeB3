#pragma once
#include "SFML/Graphics.hpp"
#include "models/Level.h"
#include "managers/LevelManager.h"
#include "EntityManager.h"
#include <managers/RenderManager.h>
class GameEngine
{
public:
	virtual ~GameEngine();
	GameEngine(const GameEngine& _other) = delete;
	void operator =(const GameEngine& _other) = delete;
	static GameEngine* GetInstance();
	bool Run();
	sf::RenderWindow* GetWindow();
	float GetDeltaTime();
private:
	GameEngine() = default;
	void Start();
	void Update();
	void Render();
	bool LoadResources();
	static GameEngine* m_engine;
	sf::Clock m_clock;
	void ResetTime();
	sf::RenderWindow* m_window;
	LevelManager* m_level;
	EntityManager* m_entityManager;
	RenderManager* m_renderManager;
};
