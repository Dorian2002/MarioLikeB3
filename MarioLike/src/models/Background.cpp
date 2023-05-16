#include "models/Background.h"
#include "component/BoxColliderComponent.h"

Background::Background(Vec2f position)
{
	Components = { new Transform(this,position), new SpriteComponent(this, "Background", {500, 500})};
}


void Background::Start()
{
	std::cout << GetClassRttiName() << std::endl;
	Entity::Start();
}

void Background::Update(float deltaT)
{
	Entity::Update(deltaT);
}