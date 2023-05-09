#pragma once
#include "utils/Sling.h"
#include "SFML/Graphics.hpp"
#include <unordered_map>

using SignalMap = std::unordered_map<sf::Keyboard::Key, Event::Signal<>*>;
enum KeyInput
{
	onKeyPress,
	onKeyHeld,
	onKeyRelease,
};

class InputManager
{
public:
	virtual ~InputManager();
	InputManager(const InputManager& _other) = delete;
	void operator =(const InputManager& _other) = delete;
	void HandleInput();
	static InputManager* GetInstance();
	void AddKeyBind(sf::Keyboard::Key key, Event::Slot<>* slot, KeyInput state = onKeyHeld);
	void RemoveKeyBind(sf::Keyboard::Key key, Event::Slot<>* slot);
	void ClearKeyBinds();
private:
	InputManager();
	sf::RenderWindow* m_window;
	std::unordered_map<KeyInput, SignalMap> m_signals;
	std::unordered_map<sf::Keyboard::Key, bool> m_keyPressed;
	static InputManager* m_instance;
	
};

