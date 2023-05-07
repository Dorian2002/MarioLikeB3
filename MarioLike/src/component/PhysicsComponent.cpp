#include "component/PhysicsComponent.h"
#include "component/Transform.h"
#include "engine/GameEngine.h"


PhysicsComponent::PhysicsComponent(Entity* root, bool isKinematic)
{
    m_isKinematic = isKinematic;
    m_root = root;
    velocity = { 0,0 };
    isGrounded = false;
}

void PhysicsComponent::Update(float deltaT)
{
    if (m_isKinematic) {
        jumpForce += 100000 * deltaT;
        velocity.y += jumpForce * deltaT;
        Transform* t = m_root->GetComponent<Transform>();
        auto lastPos = t->GetPosition();
        t->Translate(0, 0, velocity.y);
        if (!EntityManager::GetInstance()->MoveEntity(m_root))
        {
            velocity.y = 0;
            t->SetPosition(lastPos);
            isGrounded = true;
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