#pragma once
#include "models/GameObject.h"
#include "models/Component.h"
#include <unordered_map>
#include "utils/Vector2.h"
#include "component/Transform.h"
#include "component/SpriteComponent.h"
#include <iostream>
#include <map>
#include <string>

class Entity : public GameObject {
public:
	void Start() override;
	static const int id;
	std::vector<Component*> Components;
	template<typename T>
	T* GetComponent();

	Entity() {};
	Entity(Vec2f _spriteSize);
	~Entity() = default;
	
	private:
		std::map<std::string, int> tab;
};

template<typename T>
inline T* Entity::GetComponent()
{
	for (auto component : Components) {
		auto* res = dynamic_cast<T*>(component);
		if (res != nullptr)
			return res;
	}
	return nullptr;
}
