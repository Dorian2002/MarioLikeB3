#pragma once
#include <SFML/Graphics.hpp>
class UIButton;

class Menu {
public:
	Menu(sf::RenderWindow*);
	~Menu();
	void HandleEvents(sf::Event*);
	void DrawMenu();
	sf::Texture* m_texture ;
	sf::Sprite* m_background;
	UIButton* m_playButton;
	UIButton* m_quitButton;
	sf::RenderWindow* m_window;
};