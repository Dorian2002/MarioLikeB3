#pragma once
#include <SFML/Graphics.hpp>
#include "models/GameObject.h"

class UIGameLevel : public GameObject{
public:
	UIGameLevel(sf::RenderWindow* window);
	~UIGameLevel();
	sf::RenderWindow* m_window;
	void Update(float) override;
	sf::Text* m_coinText;
	int* m_coinCount;
};
