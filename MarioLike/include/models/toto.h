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
#include <component/Animator.h>
#include <iostream>
#include "managers/InputManager.h"
#include "engine/GameEngine.h"
#include "utils/Anim/Animations/MarioRun.h"
#include "utils/Anim/Animations/MarioIdle.h"

class toto : public Entity
{
public:
    bool m_isWalking;
    Vec2f velocity;
    DEFINE_RTTI(toto);
    toto() {
        MarioRun* run = new MarioRun(AssetManager::GetInstance()->GetTexture("littleMarioRun"), 3);
        MarioIdle* idle = new MarioIdle(AssetManager::GetInstance()->GetTexture("littleMarioIdle"), 1);
        Components = {
            new Transform(this, {2,10}),
            new SpriteComponent(this, "littleMarioIdle"),
            new PhysicsComponent(this, true),
            new BoxColliderComponent(this, new Vec2f{16,16}),
            new Animator(
                this,
                std::vector<Animation*>{
                    run, 
                    idle 
                }
            )
        };
        SetUpAnimatorLink(run, idle);
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
        if (velocity.x < 0.1 && velocity.x > -0.1) {
            m_isWalking = false;
        }
    }

    void MoveRight()
    {
        m_isWalking = true;
        auto t = GetComponent<Transform>();
        auto lastPos = t->GetPosition();
        if (velocity.x < 0.1) {
            velocity.x += 0.1;
        }
        t->Translate(0, velocity.x, 0);


        auto sprite = GetComponent<SpriteComponent>()->m_sprite;
        sprite->setOrigin({ sprite->getLocalBounds().width, 0 });
        sprite->setScale({ -1, 1 });


        if (!EntityManager::GetInstance()->MoveEntity(this))
        {
            t->SetPosition(lastPos);
        }
    }
    void MoveLeft()
    {
        m_isWalking = true;

        auto t = GetComponent<Transform>();
        auto lastPos = t->GetPosition();
        if (velocity.x > -0.1) {
            velocity.x += -0.1;
        }
        t->Translate(0, velocity.x, 0);


        auto spriteComponent = GetComponent<SpriteComponent>();
        spriteComponent->m_sprite->setOrigin({ spriteComponent->m_sprite->getLocalBounds().width - spriteComponent->m_spriteSize.x, 0});
        spriteComponent->m_sprite->setScale({ 1, 1 });


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

    void IsWalking(bool val) {
        if (m_isWalking == val) {
            GetComponent<Animator>()->m_changeAnim = true;
        }
        return;
    }

    void SetUpAnimatorLink(Animation* run, Animation* idle) {
        Animator* animator = GetComponent<Animator>();

        Event::Signal<bool>* sigRunToIdle = new Event::Signal<bool>();
        sigRunToIdle->connect(new Event::Slot<bool>(this, &toto::IsWalking));
        animator->CreateLink(run, idle, sigRunToIdle, false);

        Event::Signal<bool>* sigIdleToRun = new Event::Signal<bool>();
        sigIdleToRun->connect(new Event::Slot<bool>(this, &toto::IsWalking));
        animator->CreateLink(idle, run, sigIdleToRun, true);
    }
};