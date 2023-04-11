#pragma once
#include "SFML/Graphics.hpp"
<<<<<<< HEAD
#include "models/Level.h"
#include "managers/LevelManager.h"
#include "EntityManager.h"
#include <managers/RenderManager.h>
=======
#include "manager/InputManager.h"
>>>>>>> 5e19e8e... Input Manager WIP
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
	void HandleInput();
	void Update();
	void Render();
	bool LoadResources();
	static GameEngine* m_engine;
	sf::Clock m_clock;
	void ResetTime();
	sf::RenderWindow* m_window;
<<<<<<< HEAD
	LevelManager* m_level;
	EntityManager* m_entityManager;
	RenderManager* m_renderManager;
=======
	InputManager* m_inputManager;
>>>>>>> 5e19e8e... Input Manager WIP
};
