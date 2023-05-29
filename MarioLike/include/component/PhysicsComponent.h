#pragma once

#include "models/Component.h"
#include "utils/Vector2.h"

class PhysicsComponent : public Component
{
public:
    DEFINE_RTTI(PhysicsComponent)
	PhysicsComponent(Entity*, bool);
    void Update(float) override;
    void Start() override;
    void Move(Vec2f dist);
    bool GetIsKinematic();
    void SetIsKinematic(bool);
    Vec2f m_velocity;
    bool m_isGrounded;
    float m_jumpForce = 0;
    bool m_isJumping = true;
    float m_maxVel = 0;
private:
    bool m_isKinematic;
};
