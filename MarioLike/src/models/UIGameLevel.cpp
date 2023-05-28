#include "models/UIGameLevel.h"
#include "managers/AssetManager.h"
#include "managers/EntityManager.h"
#include "models/Player.h"
#include "SFML/Graphics.hpp"

UIGameLevel::UIGameLevel(sf::RenderWindow* window) {
    m_window = window;
    m_coinCount = EntityManager::GetInstance()->m_player->GetCoinCount();
    m_coinText = new sf::Text;
    m_coinText->setCharacterSize(60);
    m_coinText->setFont(*AssetManager::GetInstance()->GetFont("mainFont"));
    m_coinText->setFillColor(sf::Color::White);
    sf::FloatRect textBounds = m_coinText->getLocalBounds();
    m_coinText->setPosition(30 + (100 - textBounds.width) / 2, 500 + ( 50 - textBounds.height) / 2);
}

UIGameLevel::~UIGameLevel() {
    m_window = nullptr;
    delete m_coinText;
    m_coinText = nullptr;
    m_coinCount = nullptr;
}

void UIGameLevel::Update(float)
{
    m_coinText->setString(std::to_string(*m_coinCount));
    m_window->draw(*m_coinText);
}
