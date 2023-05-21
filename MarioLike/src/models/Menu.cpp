#include "models/Menu.h"
#include "managers/AssetManager.h"
#include "engine/GameEngine.h"
#include "utils/Button.h"

Menu::Menu(sf::RenderWindow* window)
{
	m_window = window;

	m_texture = AssetManager::GetInstance()->GetTexture("menuBackground");
	m_background = new sf::Sprite();
	m_background->setScale(0.5, 0.5);
	m_background->setTexture(*m_texture);

	m_playButton = new UIButton(sf::Vector2f(30, 150), sf::Vector2f(100, 50));
	m_playButton->setOnClickCallback([this]() {
		GameEngine::GetInstance()->RunGame();
		});
	m_playButton->setText("PLAY");

	m_quitButton = new UIButton(sf::Vector2f(30, 450), sf::Vector2f(80, 40));
	m_quitButton->setOnClickCallback([this]() {
		GameEngine::GetInstance()->GetWindow()->close();
		});
	m_quitButton->setText("QUIT");
}

Menu::~Menu()
{
	delete m_background;
	m_background = nullptr;
	delete m_texture;
	m_texture = nullptr;
	delete m_playButton;
	m_playButton = nullptr;
	delete m_quitButton;
	m_quitButton = nullptr;
}

void Menu::HandleEvents(sf::Event* event)
{
	m_playButton->handleEvent(event, m_window);
	m_quitButton->handleEvent(event, m_window);
}

void Menu::DrawMenu() 
{
	m_window->draw(*m_background);
	m_playButton->draw(m_window);
	m_quitButton->draw(m_window);
}
