#pragma once
#include "Entity.h"
#include "utils/Rtti.h"
#include "component/PhysicsComponent.h"
#include <component/SpriteComponent.h>

class Coin : public Entity, public Rtti
{
public:
	DEFINE_RTTI(Coin)
	Coin(Vec2f);
	void Start() override;
	void Update(float deltaT) override;
	void OnOverlap(Component* overlapComponent, Entity* overlapEntity) override;
};