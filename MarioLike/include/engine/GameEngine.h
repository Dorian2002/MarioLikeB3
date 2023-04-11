#pragma once
#include "SFML/Graphics.hpp"
#include "manager/InputManager.h"
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
	static GameEngine* m_engine;
	sf::Clock m_clock;
	void ResetTime();
	sf::RenderWindow* m_window;
	InputManager* m_inputManager;
};

