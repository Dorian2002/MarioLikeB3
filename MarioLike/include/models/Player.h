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

class Player : public Entity
{
public:
    bool m_isWalking;
    Vec2f velocity;
    DEFINE_RTTI(Player);

    Player();

    void Start() override;

    void Update(float deltaT) override;

    void MoveRight();

    void MoveLeft();

    void jump();

    void IsWalking(bool val);

    void SetUpAnimatorLink(Animation* run, Animation* idle);
};