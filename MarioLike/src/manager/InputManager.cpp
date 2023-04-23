#include "manager/InputManager.h"
#include <iostream>

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
	for(int c :m_binds)
	{
		std::cout << c << std::endl;
	}
}

void InputManager::AddSlot(sf::Keyboard& key, Event::Slot slot)
{
	int index = *std::find(m_binds, m_binds + std::size(m_binds), key);
	m_signals[index].connect(slot);
}

void InputManager::RemoveSlot(sf::Keyboard& key, Event::Slot* slot)
{
	int index = *std::find(m_binds, m_binds + std::size(m_binds), key);
	m_signals[index].disconnect(slot);
}

void InputManager::ClearSignals()
{
	for(auto& it : m_signals)
	{
		it.clear();
	}
}
