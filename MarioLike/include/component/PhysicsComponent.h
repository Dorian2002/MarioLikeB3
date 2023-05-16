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
    bool GetIsKinematic();
    void SetIsKinematic(bool);
    Vec2f velocity;
    bool isGrounded;
    float jumpForce = 0;
    bool isJumping = true;
    float maxVel = 0;
private:
    bool m_isKinematic;
};
