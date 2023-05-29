#include "models/Entity.h"
#include <managers/AssetManager.h>

void Entity::Start()
{

}

void Entity::Update(float deltaT)
{
	for (auto& component : Components) {
		if (component != nullptr)
			component->Update(deltaT);
	}
}

Entity::Entity(Vec2f _spriteSize)
{
}

Entity::~Entity()
{
	for (std::size_t i = 0; i< Components.size(); i++)
	{
		Components[i]->Destroy();
		delete Components[i];
	}
	Components.clear();
}

void Entity::OnOverlap(Component* overlapComponent, Entity* overlapEntity)
{
	return;
}

void Entity::OnCollide(Component* overlapComponent, Entity* overlapEntity)
{
	return;
}
