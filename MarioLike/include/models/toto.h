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
#include "managers/InputManager.h"

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
		auto inputManager = InputManager::GetInstance();
		inputManager->AddSlot(sf::Keyboard::Q, new Event::Slot<>(this, &toto::MoveLeft));
		inputManager->AddSlot(sf::Keyboard::D, new Event::Slot<>(this, &toto::MoveRight));
	};
	void Update(float deltaT) override {
		Entity::Update(deltaT);


	}

	void MoveRight()
	{
		auto t = GetComponent<Transform>();
		t->Translate(0, 0.1, 0);
	}
	void MoveLeft()
	{
		auto t = GetComponent<Transform>();
		t->Translate(0, -0.1, 0);
	}
};