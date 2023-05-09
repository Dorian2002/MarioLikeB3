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
        Components = { new Transform(this, {1,0}), new SpriteComponent(this, "petitMario"), new PhysicsComponent(this, true) };
    }
    void Start() override {
        std::cout << GetClassRttiName() << std::endl;
        Entity::Start();
        auto inputManager = InputManager::GetInstance();
        inputManager->AddKeyBind(sf::Keyboard::Q, new Event::Slot<>(this, &toto::MoveLeft));
        inputManager->AddKeyBind(sf::Keyboard::D, new Event::Slot<>(this, &toto::MoveRight), onKeyHeld);
        inputManager->AddKeyBind(sf::Keyboard::Space, new Event::Slot<>(this, &toto::jump), KeyInput::onKeyPress);
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
    void jump()
    {
        auto t = GetComponent<PhysicsComponent>();
        t->velocity.y = -sqrt(100000000 * 9.81);
    }
};