#pragma once
#include "Ennemy.h"
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
#include <component/BT/BoombaBT.h>
#include <iostream>
#include "engine/GameEngine.h"
#include "utils/Anim/Animations/BoombaRun.h"
#include "utils/Anim/Animations/BoombaIdle.h"

class Boomba : public Ennemy
{
public:
    bool m_isWalking;
    Vec2f velocity;
    DEFINE_RTTI(Boomba);
    bool left = false;
    bool right = false;

    Boomba();

    void Start() override;

    void Update(float deltaT) override;

    void StartRight();

    void StopRight();

    void StopLeft();

    void StartLeft();

    bool MoveRight() override;

    bool MoveLeft() override;

    void IsWalking(bool val);

    void SetUpAnimatorLink(Animation* run, Animation* idle);

};
