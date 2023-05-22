#include "component/PhysicsComponent.h"
#include "component/SpriteComponent.h"
#include "component/Transform.h"
#include "engine/GameEngine.h"
#include "models/Entity.h"
#include "managers/EntityManager.h"
#include "models/Boomba.h"
#include "models/Player.h"


PhysicsComponent::PhysicsComponent(Entity* root, bool isKinematic)
{
    m_isKinematic = isKinematic;
    m_root = root;
    velocity = { 0,0 };
    isGrounded = false;
}

void PhysicsComponent::Update(float deltaT)
{

    if (isGrounded)
    {
        isGrounded = !EntityManager::GetInstance()->MoveEntity(m_root, Vec2f{ 0, 9.81f * deltaT * 0.005f }, false);
    }

    if (m_isKinematic) {
        if (!isGrounded)
        {
            velocity.y += 9.81f * deltaT * 2;
        }
        Move(velocity * deltaT);

        if (m_root->GetComponent<SpriteComponent>()->m_sprite->getPosition().y > GameEngine::GetInstance()->GetWindow()->getSize().y)
        {
	        if (m_root->GetClassRttiName() == Player::GetStaticRName())
	        {
                GameEngine::GetInstance()->BackToMenu();
	        }
            else if (m_root->GetClassRttiName() == Boomba::GetStaticRName())
            {
                EntityManager::GetInstance()->DeferDeleteEntity(m_root);
            }
        }

    }
}

//void PhysicsComponent::Move (float dist)
//{
//    float val = 0.99f;
//    bool isNegative = dist < 0;
//    if (isNegative)
//        dist = -dist;
//    while (dist > val)
//    {
//        if (!EntityManager::GetInstance()->MoveEntity(m_root, Vec2f(0, isNegative ? -val : val)))
//        {
//            if (velocity.y > 0)
//            {
//                isGrounded = true;
//                isJumping = false;
//            }
//            velocity.y = 0;
//            break;
//        }
//        dist -= val;
//    }
//    if (isNegative)
//    {
//        if (-dist < 0 && -dist >= -val)
//        {
//            if(!EntityManager::GetInstance()->MoveEntity(m_root, Vec2f(0,-dist)))
//            {
//                velocity.y = 0;
//            }
//        }
//    }
//    else
//    {
//        if (dist > 0 && dist <= val)
//        {
//            if(!EntityManager::GetInstance()->MoveEntity(m_root, Vec2f(0, dist)))
//            {
//                isGrounded = true;
//                isJumping = false;
//                velocity.y = 0;
//            }
//        }
//    }
//}

void PhysicsComponent::Move (Vec2f dist)
{
    constexpr float val = 0.99f;
    const bool isNegativeX = dist.x < 0;
    const bool isNegativeY = dist.y < 0;
    dist.x = abs(dist.x);
    dist.y = abs(dist.y);
    while(dist.x > 0)
    {
	    if(dist.x < val)
	    {
            if (!EntityManager::GetInstance()->MoveEntity(m_root, Vec2f(isNegativeX ? -dist.x : dist.x, 0)))
            {
                velocity.x = 0;
                break;
            }
            dist.x = 0;
	    }
        else
        {
            if (!EntityManager::GetInstance()->MoveEntity(m_root, Vec2f(isNegativeX ? -val : val, 0)))
            {
                velocity.x = 0;
                break;
            }
            dist.x -= val;
        }
    }
    while(dist.y > 0)
    {
	    if (dist.y < val)
	    {
            if (!EntityManager::GetInstance()->MoveEntity(m_root, Vec2f(0, isNegativeY ? -dist.y : dist.y)))
            {
                if (velocity.y > 0)
                {
                    isGrounded = true;
                    isJumping = false;
                }
                velocity.y = 0;
                break;
            }
            dist.y = 0;
	    }
        else
        {
            if (!EntityManager::GetInstance()->MoveEntity(m_root, Vec2f(0, isNegativeY ? -val : val)))
            {
                if (velocity.y > 0)
                {
                    isGrounded = true;
                    isJumping = false;
                }
                velocity.y = 0;
                break;
            }
            dist.y -= val;
        }
    }
}

void PhysicsComponent::Start()
{
}

bool PhysicsComponent::GetIsKinematic()
{
    return m_isKinematic;
}

void PhysicsComponent::SetIsKinematic(bool value)
{
    m_isKinematic = value;
}