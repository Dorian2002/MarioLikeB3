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
    bool left = false;
    bool right = false;
    float maxDist = 0;
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
        Entity::Start();
        auto inputManager = InputManager::GetInstance();
        /*inputManager->AddKeyBind(sf::Keyboard::Q, new Event::Slot<>(this, &toto::MoveLeft));
        inputManager->AddKeyBind(sf::Keyboard::D, new Event::Slot<>(this, &toto::MoveRight));*/
        inputManager->AddKeyBind(sf::Keyboard::Q, new Event::Slot<>(this, &toto::StartLeft), onKeyPress);
        inputManager->AddKeyBind(sf::Keyboard::D, new Event::Slot<>(this, &toto::StartRight), onKeyPress);
        inputManager->AddKeyBind(sf::Keyboard::Q, new Event::Slot<>(this, &toto::StopLeft), onKeyRelease);
        inputManager->AddKeyBind(sf::Keyboard::D, new Event::Slot<>(this, &toto::StopRight), onKeyRelease);
        inputManager->AddKeyBind(sf::Keyboard::Space, new Event::Slot<>(this, &toto::jump), onKeyPress);
    };

    void Update(float deltaT) override {
        Entity::Update(deltaT);
        if (left)
        {
            SetVelX(-0.1f);
            auto spriteComponent = GetComponent<SpriteComponent>();
            spriteComponent->m_sprite->setOrigin({ spriteComponent->m_sprite->getLocalBounds().width - spriteComponent->m_spriteSize.x, 0 });
            spriteComponent->m_sprite->setScale({ 1, 1 });
        }
        if (right)
        {
            SetVelX(0.1f);
            auto sprite = GetComponent<SpriteComponent>()->m_sprite;
            sprite->setOrigin({ sprite->getLocalBounds().width, 0 });
            sprite->setScale({ -1, 1 });
        }
        if (!left && !right)
        {
            if (velocity.x > 0)
            {
                SetVelX(-0.1f);
            }
            if (velocity.x < 0)
            {
                SetVelX(0.1f);
            }
        }
        if (velocity.x < 0.1 && velocity.x > -0.1) {
            velocity.x = 0;
        }
        auto t = GetComponent<Transform>();
        auto lastPos = t->GetPosition();
        auto dist = velocity.x * deltaT * 10000;
        bool collide = false;

        // TODO : refactor
        if (dist > 0)
        {
            while (dist > 0.99f)
            {
                t->Translate(0, 0.99f, 0);
                if (!EntityManager::GetInstance()->MoveEntity(this))
                {
                    t->SetPosition(lastPos);
                    collide = true;
                    break;
                }
                    lastPos = t->GetPosition();
                dist -= 0.99f;
            }
            if (!collide)
            {
                t->Translate(0, dist, 0);
                if (!EntityManager::GetInstance()->MoveEntity(this))
                {
                    t->SetPosition(lastPos);
                }
            }
        } else
        {
            while (dist < -0.99f)
            {
                t->Translate(0, -0.99f, 0);
                if (!EntityManager::GetInstance()->MoveEntity(this))
                {
                    t->SetPosition(lastPos);
                    collide = true;
                    break;
                }
                    lastPos = t->GetPosition();
                dist += 0.99f;
            }
            if(!collide)
            {
	            t->Translate(0, dist, 0);
	            if (!EntityManager::GetInstance()->MoveEntity(this))
	            {
	                t->SetPosition(lastPos);
	            }
            }
        }
    }

    void SetVelX(float acceleration)
    {
        velocity.x = std::clamp(velocity.x + acceleration, -2.f, 2.f);
    }

    void StartRight()
    {
        right = true;
    }

    void StopRight()
    {
        right = false;
    }

    void StopLeft()
    {
        left = false;
    }

    void StartLeft()
    {
        left = true;
    }

    void jump()
    {
        auto t = GetComponent<PhysicsComponent>();
        if (t->isGrounded) {
            auto t = GetComponent<PhysicsComponent>();
            if (t->isGrounded) {
                t->jumpForce = -20;
                t->isGrounded = false;
                t->isJumping = true;
            }
        }
    }

    void IsWalking(bool val) {
        if ((velocity.x!= 0) == val) {
            GetComponent<Animator>()->m_changeAnim = true;
        }
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