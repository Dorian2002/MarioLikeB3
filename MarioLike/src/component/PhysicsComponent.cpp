#include "component/PhysicsComponent.h"
#include "component/Transform.h"
#include "models/Entity.h"
#include "managers/EntityManager.h"


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
        isGrounded = !EntityManager::GetInstance()->MoveEntity(m_root, Vec2f{0, 9.81f * deltaT * 0.005f }, false);
    }
    if (m_isKinematic) {
        if(isJumping && jumpForce < 0)
        {
            jumpForce += 9.81f * deltaT * 0.005f;
            velocity.y += jumpForce * deltaT * 0.5f;
        }
        if(!isGrounded)
        {
            velocity.y += 9.81f * deltaT * 0.005f;
        }
        if(velocity.y > maxVel)
        {
            maxVel = velocity.y;
        }
        velocity.y = std::min(velocity.y, 0.034f);
        //std::cout << "maxvel: " << maxVel << std::endl;
        Transform* t = m_root->GetComponent<Transform>();
        auto lastPos = t->GetPosition();
        t->Translate(0, 0, velocity.y);
        if (!EntityManager::GetInstance()->MoveEntity(m_root))
        {
            velocity.y = 0;
            t->SetPosition(lastPos);
            isGrounded = true;
            isJumping = false;
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