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
    bool m_left = false;
    bool m_right = false;
    Vec2f m_lastPosition;
    DEFINE_RTTI(Player);

    Player();

    void Start() override;

    void Update(float deltaT) override;

    void Move(float dist);

    void SetVelX(float acceleration, float min = -6.f, float max = 6.f);

    void StartRight();

    void StopRight();

    void StopLeft();

    void StartLeft();

    void Jump();

    bool IsWalking();

    void OnCollide(Component* overlapComponent, Entity* overlapEntity) override;

    void OnOverlap(Component* overlapComponent, Entity* overlapEntity) override;
    int* GetCoinCount();

    void SetUpAnimatorLink(Animation* run, Animation* idle);

    void AnimIsWalking(bool val);


private:
    float m_speedCoefficient = 1.0f;
    int m_coins = 0;
};