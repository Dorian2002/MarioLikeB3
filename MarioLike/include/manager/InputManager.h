#pragma once
#include "utils/Sling.h"
#include "SFML/Graphics.hpp"

DECLARE_DELEGATE(FOnInputPressed);

class InputManager
{
public:
	virtual ~InputManager();
	InputManager(const InputManager& _other) = delete;
	void operator =(const InputManager& _other) = delete;
	static InputManager* GetInstance();
	void AddSlot(sf::Keyboard& key, Event::Slot<void>* slot);
	void RemoveSlot(sf::Keyboard& key, Event::Slot<void>* slot);
	void ClearSignals();
private:
	InputManager();
	std::vector<FOnInputPressed> m_signals;
	static InputManager* m_instance;
	static inline int m_binds[] {sf::Keyboard::Z, sf::Keyboard::Q, sf::Keyboard::S,sf::Keyboard::D, sf::Keyboard::Escape};
};

