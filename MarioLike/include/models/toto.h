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
#include "engine/GameEngine.h"

class toto : public Entity
{
public:
    DEFINE_RTTI(toto);


    Vec2f m_lastposition;

    toto() {
        Components = { new Transform(this, {2,10}), new SpriteComponent(this, "petitMario"), new PhysicsComponent(this, true), new BoxColliderComponent(this, new Vec2f{16,12})};
    }
    void Start() override {
        std::cout << GetClassRttiName() << std::endl;
        Entity::Start();
        auto inputManager = InputManager::GetInstance();
        inputManager->AddSlot(sf::Keyboard::Q, new Event::Slot<>(this, &toto::MoveLeft));
        inputManager->AddSlot(sf::Keyboard::D, new Event::Slot<>(this, &toto::MoveRight));
        inputManager->AddSlot(sf::Keyboard::Space, new Event::Slot<>(this, &toto::jump));
    };
    void Update(float deltaT) override {
        Entity::Update(deltaT);
    }

    void MoveRight()
    {
        auto t = GetComponent<Transform>();
        auto lastPos = t->GetPosition();
        m_lastposition = t->m_position;
        t->Translate(0, 0.1, 0);
        if (!EntityManager::GetInstance()->MoveEntity(this))
        {
            t->SetPosition(lastPos);
        }
    }
    void MoveLeft()
    {
        auto t = GetComponent<Transform>();
        auto lastPos = t->GetPosition();
        m_lastposition = t->m_position;
        t->Translate(0, -0.1, 0);
        if (!EntityManager::GetInstance()->MoveEntity(this))
        {
            t->SetPosition(lastPos);
        }
    }
    void jump()
    {
        auto t = GetComponent<PhysicsComponent>();
        if (t->isGrounded) {
            float deltaT = GameEngine::GetInstance()->GetDeltaTime();
            t->isGrounded = false;
            t->jumpForce -= 200000*deltaT;
        }
    }
};