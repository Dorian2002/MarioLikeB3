#pragma once
#include "Entity.h"
#include "utils/Rtti.h"
#include "models/Entity.h"
#include <memory>
#include "models/Component.h"
#include "component/PhysicsComponent.h"
#include <component/TestComponent.h>
#include <component/Transform.h>
#include <component/SpriteComponent.h>
#include <iostream>

class Block : public Entity, public Rtti
{
public:
	DEFINE_RTTI(Block)
	Block(Vec2f);
	void Start() override;
	void Update(float deltaT) override;
};