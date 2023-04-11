#pragma once
#include "models/GameObject.h"
#include "models/Component.h"
#include <unordered_map>
#include <iostream>

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
};