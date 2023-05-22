#pragma once
#include "models/Entity.h"

class Finish : public Entity {
public:
    DEFINE_RTTI(Finish)
        Finish(Vec2f);
    void Start() override;
    void Update(float deltaT) override;
    void OnOverlap(Component* overlapedComponent, Entity* overlapedEntity) override;
};