#pragma once
#include "Entity.h"
#include "utils/Rtti.h"
#include "component/PhysicsComponent.h"
#include <component/SpriteComponent.h>

class Block : public Entity, public Rtti
{
public:
	DEFINE_RTTI(Block)
	Block(Vec2f);
	void Start() override;
	void Update(float deltaT) override;
};