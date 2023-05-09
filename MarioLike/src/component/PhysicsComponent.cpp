#include "component/PhysicsComponent.h"
#include "component/Transform.h"
#include "engine/GameEngine.h"


PhysicsComponent::PhysicsComponent(Entity* root, bool isKinematic)
{
    m_isKinematic = isKinematic;
    m_root = root;
    velocity = { 0,0 };
}

void PhysicsComponent::Update(float deltaT)
{
    if (m_isKinematic && deltaT < 0.03) {
        velocity.y += 10000000*9.81 * deltaT;
        Transform* t = m_root->GetComponent<Transform>();
        auto lastPos = t->GetPosition();
        t->Translate(0, 0, velocity.y * deltaT);
        if (!EntityManager::GetInstance()->MoveEntity(t))
        {
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