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
        isGrounded = !EntityManager::GetInstance()->MoveEntity(m_root, Vec2f{ 0, 9.81f * deltaT * 0.005f }, false);
    }

    if (m_isKinematic) {
        if (!isGrounded)
        {
            velocity.y += 9.81f * deltaT * 2;
        }
        Transform* t = m_root->GetComponent<Transform>();
        auto lastPos = t->GetPosition();
        t->Translate(0, 0, velocity.y * deltaT);

        if (!EntityManager::GetInstance()->MoveEntity(m_root))
        {
            if (velocity.y > 0) {
                isGrounded = true;
                isJumping = false;
            }
            velocity.y = 0;
            t->SetPosition(lastPos);
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