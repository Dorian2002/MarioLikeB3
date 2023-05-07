#pragma once
#include "utils/Sling.h"
#include "SFML/Graphics.hpp"
#include <unordered_map>

DECLARE_DELEGATE(FOnInputPressed);

class InputManager
{
public:
	virtual ~InputManager();
	InputManager(const InputManager& _other) = delete;
	void operator =(const InputManager& _other) = delete;
	void HandleInput();
	static InputManager* GetInstance();
	void AddSlot(sf::Keyboard::Key key, Event::Slot<>* slot);
	void RemoveSlot(sf::Keyboard::Key key, Event::Slot<>* slot);
	void ClearSignals();
private:
	InputManager();
	sf::RenderWindow* m_window;
	std::unordered_map<sf::Keyboard::Key, Event::Signal<>*> m_signals;
	static InputManager* m_instance;
	
};

