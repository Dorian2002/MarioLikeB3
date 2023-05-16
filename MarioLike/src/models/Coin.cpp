#include "models/Coin.h"
#include "component/BoxColliderComponent.h"

Coin::Coin(Vec2f position)
{
	Components = { new Transform(this,position), new SpriteComponent(this, "coin"), new BoxColliderComponent(this,new Vec2f({16,16}), false) };
}


void Coin::Start()
{
	std::cout << GetClassRttiName() << std::endl;
	Entity::Start();
}

void Coin::Update(float deltaT)
{
	Entity::Update(deltaT);
}

void Coin::OnOverlap(Component* overlapComponent, Entity* overlapEntity)
{
	
}
