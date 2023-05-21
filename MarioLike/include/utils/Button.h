#include <SFML/Graphics.hpp>
#include <functional>
#include "managers/AssetManager.h"

class UIButton {
public:
    UIButton(const sf::Vector2f& position, const sf::Vector2f& size)
    {
        m_position = position;
        m_size = size;
        m_shape.setPosition(position);
        m_shape.setSize(size);
        m_text = new sf::Text();
    }

    ~UIButton() {
        delete m_text;
        m_text = new sf::Text();
    }

    template <typename T>
    void setOnClickCallback(T&& method) {
        m_onClick = std::forward<T>(method);
    }

    void handleEvent(const sf::Event* event, const sf::RenderWindow* window) {
        if (event->type == sf::Event::MouseButtonPressed && event->mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
            sf::Vector2f convertedMousePosition = window->mapPixelToCoords(mousePosition);
            if (m_shape.getGlobalBounds().contains(convertedMousePosition)) {
                if (m_onClick) {
                    m_onClick();
                }
            }
        }
    }

    void setText(const std::string& text, const sf::Color& color, unsigned int fontSize, const sf::Font& font ) {
        m_text->setString(text);
        m_text->setCharacterSize(fontSize);
        m_text->setFont(font);
        m_text->setFillColor(color);
        sf::FloatRect textBounds = m_text->getLocalBounds();
        m_text->setPosition(m_position.x + (m_size.x - textBounds.width) / 2, m_position.y + (m_size.y - textBounds.height) / 2);
    }
    void setText(const std::string& text, unsigned int fontSize, const sf::Font& font) {
        m_text->setString(text);
        m_text->setCharacterSize(fontSize);
        m_text->setFont(font);
        m_text->setFillColor(sf::Color::Black);
        sf::FloatRect textBounds = m_text->getLocalBounds();
        m_text->setPosition(m_position.x + (m_size.x - textBounds.width) / 2, m_position.y + (m_size.y - textBounds.height) / 2);
    }
    void setText(const std::string& text, unsigned int fontSize, const sf::Color& color) {
        m_text->setString(text);
        m_text->setCharacterSize(fontSize);
        m_text->setFont(*AssetManager::GetInstance()->GetFont("mainFont"));
        m_text->setFillColor(color);
        sf::FloatRect textBounds = m_text->getLocalBounds();
        m_text->setPosition(m_position.x + (m_size.x - textBounds.width) / 2, m_position.y + (m_size.y - textBounds.height) / 2);
    }
    void setText(const std::string& text) {
        m_text->setString(text);
        m_text->setCharacterSize(30);
        m_text->setFont(*AssetManager::GetInstance()->GetFont("mainFont"));
        m_text->setFillColor(sf::Color::Black);
        sf::FloatRect textBounds = m_text->getLocalBounds();
        m_text->setPosition(m_position.x + (m_size.x - textBounds.width) / 2, m_position.y + (m_size.y - textBounds.height) / 2);
    }

    void draw(sf::RenderWindow* window) {
        window->draw(m_shape);
        window->draw(*m_text);
    }

private:
    sf::Vector2f m_position;
    sf::Vector2f m_size;
    sf::RectangleShape m_shape;
    sf::Text* m_text;
    std::function<void()> m_onClick;
};