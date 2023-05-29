#include "models/Background.h"
#include "component/BoxColliderComponent.h"

Background::Background(Vec2f position)
{
	Components = { new Transform(this,position), new SpriteComponent(this, "Background", {960, 540})};
}


void Background::Start()
{
	Entity::Start();
}

void Background::Update(float deltaT)
{
	Entity::Update(deltaT);
}