#pragma once
#include "models/Component.h"
#include <vector>
#include "utils/Anim/Animation.h"
#include "utils/Anim/Link.h"
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
private:
    bool m_isKinematic;

};
