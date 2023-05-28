#include "models/Finish.h"
#include "component/Transform.h"
#include "component/SpriteComponent.h"
#include "models/Player.h"
#include "component/BoxColliderComponent.h"

Finish::Finish(Vec2f position)
{
    Vec2f Size = { 25, 87 };
    position.y = position.y - (Size.y - 16) / 16;
    Components = { new Transform(this,position), new SpriteComponent(this, "flag", Size), new BoxColliderComponent(this, {25,87}, false) };
}

void Finish::Start()
{
    std::cout << GetClassRttiName() << std::endl;
    Entity::Start();
}

void Finish::Update(float deltaT)
{
    Entity::Update(deltaT);
}

void Finish::OnOverlap(Component* overlapedComponent, Entity* overlapedEntity)
{
    GameEngine::GetInstance()->BackToMenu();
}