#pragma once
#include "utils/Rtti.h"
#include "models/Entity.h"
#include <memory>
#include "models/Component.h"
#include <component/TestComponent.h>
#include <component/Transform.h>
#include <component/SpriteComponent.h>
#include <iostream>

class toto : public Entity
{
public:
	DEFINE_RTTI(toto);
	toto() {
		Components = { new TestComponent(), new Transform({0,0}), new SpriteComponent()};
	}
	void Start() override {
		std::cout << GetClassRttiName() << std::endl;
		Entity::Start();
	};
};