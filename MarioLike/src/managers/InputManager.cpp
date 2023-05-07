#include "managers/InputManager.h"
#include "engine/GameEngine.h"
#include <iostream>
#include "SFML/Graphics.hpp"
#include <algorithm>
#include "utils/Sling.h"
DECLARE_DELEGATE(FOnInputPressed);

InputManager* InputManager::m_instance = nullptr;

InputManager::~InputManager()
{
	delete m_instance;
	for(const auto& it : m_signals)
	{
		delete it.second;
	}
}

void InputManager::HandleInput()
{
    sf::Event e;
	while(m_window->pollEvent(e))
	{
		switch(e.type)
		{
		case sf::Event::Closed:
			m_window->close();
			break;
		case sf::Event::KeyPressed:
			auto it = m_signals.find(e.key.code);
			if (it != m_signals.end()) {
				m_signals[e.key.code]->emit();
			} else
			{
				std::cout << "Not Found\n";
			}
		}
	}
}

InputManager* InputManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new InputManager();
	}
	return m_instance;
}

InputManager::InputManager()
{
	m_window = GameEngine::GetInstance()->GetWindow();
}

void InputManager::AddSlot(sf::Keyboard::Key key, Event::Slot<>* slot)
{
	auto it = m_signals.find(key);
	if (it != m_signals.end()) {
		m_signals[key]->connect(slot);
	} else
	{
		m_signals[key] = new Event::Signal<>;
		m_signals[key]->connect(slot);
	}
	
}

void InputManager::RemoveSlot(sf::Keyboard::Key key, Event::Slot<>* slot)
{
	m_signals[key]->disconnect(slot);
}

void InputManager::ClearSignals()
{
	for(const auto& it: m_signals)
	{
		it.second->clear();
	}
}
