#pragma once
#include "utils/Rtti.h"
#include "models/Entity.h"
#include <memory>
#include "models/Component.h"
#include "component/PhysicsComponent.h"
#include <component/TestComponent.h>
#include <component/Transform.h>
#include <component/SpriteComponent.h>
#include <component/BoxColliderComponent.h>
#include <iostream>

class toto : public Entity
{
public:
	DEFINE_RTTI(toto);
	toto() {
		Components = {new Transform(this, {1,0}), new SpriteComponent(this, "petitMario"), new PhysicsComponent(this, true), new BoxColliderComponent(this, new Vec2f({12,16}))};
	}
	void Start() override {
		std::cout << GetClassRttiName() << std::endl;
		Entity::Start();
	};
	void Update(float deltaT) override {
		Entity::Update(deltaT);
	}
};