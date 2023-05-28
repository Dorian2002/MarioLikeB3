#include "models/Block.h"
#include "component/BoxColliderComponent.h"

Block::Block(Vec2f position)
{
	Components = { new Transform(this,position), new SpriteComponent(this, "block"), new BoxColliderComponent(this,{16,16})};
}


void Block::Start()
{
	std::cout << GetClassRttiName() << std::endl;
	Entity::Start();
}

void Block::Update(float deltaT)
{
	Entity::Update(deltaT);
}

