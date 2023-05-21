#include "managers/InputManager.h"
#include "engine/GameEngine.h"
#include <iostream>
#include "SFML/Graphics.hpp"
#include "utils/Sling.h"

InputManager* InputManager::m_instance = nullptr;

InputManager::~InputManager()
{
	for (const auto& it : m_signals)
	{
		for (const auto& iterator : it.second)
		{
			delete iterator.second;
		}
	}
	m_instance = nullptr;
}

void InputManager::HandleInput()
{
	using event = sf::Event;
	event e;
	while (m_window->pollEvent(e))
	{
		switch (e.type)
		{
		case event::Closed:
			m_window->close();
			break;
		case event::KeyPressed:
			if (m_signals[onKeyPress].contains(e.key.code) && !m_keyPressed[e.key.code])
			{
				m_signals[onKeyPress][e.key.code]->emit();
			}
			m_keyPressed[e.key.code] = true;
			break;
		case event::KeyReleased:
			if (m_signals[onKeyRelease].contains(e.key.code))
			{
				m_signals[onKeyRelease][e.key.code]->emit();
			}
			m_keyPressed[e.key.code] = false;
			break;
		}
	}
	for (const auto& it : m_keyPressed)
	{
		if (it.second)
		{
			if (m_signals[onKeyHeld].contains(it.first))
			{
				if (m_signals[onKeyHeld][it.first])
				{
					m_signals[onKeyHeld][it.first]->emit();
				}
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

void InputManager::AddKeyBind(sf::Keyboard::Key key, Event::Slot<>* slot, KeyInput state)
{
	if(!m_signals.contains(state))
	{
		m_signals[state] = SignalMap{};
	}
	if(!m_signals[state].contains(key))
	{
		m_signals[state][key] = new Event::Signal<>;
	}
	m_signals[state][key]->connect(slot);
}

void InputManager::RemoveKeyBind(sf::Keyboard::Key key, Event::Slot<>* slot)
{
	m_signals[onKeyHeld][key]->disconnect(slot);
}

void InputManager::ClearKeyBinds()
{
	for (const auto& it : m_signals)
	{
		for (const auto& iterator : it.second)
		{
			iterator.second->clear();
		}
	}
}
