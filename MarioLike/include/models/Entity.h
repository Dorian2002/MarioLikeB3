#pragma once
#include "models/GameObject.h"
#include "models/Component.h"
#include <unordered_map>
#include "utils/Vector2.h"
#include "component/Transform.h"
#include <iostream>
#include <map>
#include <string>

class Entity : public GameObject {
public:
	void Start() override {
		for (auto& component : Components) {
			std::cout<< " - " << component->GetClassRttiName() << std::endl;
		}
		std::cout << std::endl;  
	}
	static const int id;
	std::vector<Component*> Components;
	Transform* m_transform;
	sf::RectangleShape m_shape;
	sf::Sprite* m_sprite;
	Vec2f m_spriteSize;

	Entity() {};
	Entity(Vec2f _spriteSize);
	~Entity() = default;
	void SetSprite(const std::string& _assetId, const Vec2f& _position = { 0.f, 0.f }, const Vec2f& _size = { 0.f, 0.f });

	private:
		std::map<std::string, int> tab;
};