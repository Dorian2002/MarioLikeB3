#pragma once
#include "utils/Rtti.h"
#include "models/Entity.h"
#include <memory>
#include "models/Component.h"
#include <utils/TestComponent.h>
#include <iostream>

class toto : public Entity
{
public:
	DEFINE_RTTI(toto);
	toto() {
		Components = { new TestComponent() };
	}
	void Start() override {
		std::cout << GetClassRttiName() << std::endl;
		Entity::Start();
	};
};