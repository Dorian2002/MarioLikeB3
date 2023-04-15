#pragma once
#include "models/GameObject.h"
#include "models/Component.h"
#include <unordered_map>
#include "utils/Vector2.h"
#include "component/Transform.h"0
#include "component/SpriteComponent.h"
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

	Entity() {};
	Entity(Vec2f _spriteSize);
	~Entity() = default;
	
	private:
		std::map<std::string, int> tab;
};