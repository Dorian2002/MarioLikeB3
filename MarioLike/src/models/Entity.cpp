#include "models/Entity.h"
#include <managers/AssetManager.h>

void Entity::Start()
{
	for (auto& component : Components) {
		std::cout << " - " << component->GetClassRttiName() << std::endl;
	}
	std::cout << std::endl;
}

void Entity::Update(float deltaT)
{
	for (auto& component : Components) {
		component->Update(deltaT);
	}
}

void Entity::Destroy()
{
	for (int COMPONENT_INDEX = Components.size(); COMPONENT_INDEX >= 0; COMPONENT_INDEX--)
	{
		Components[COMPONENT_INDEX]->Destroy();
		delete Components[COMPONENT_INDEX];
		Components[COMPONENT_INDEX] = nullptr;
	}
	delete Components;
}

Entity::Entity(Vec2f _spriteSize)
{
}

void Entity::OnOverlap(Component* overlapComponent, Entity* overlapEntity)
{
	return;
}

void Entity::OnCollide(Component* overlapComponent, Entity* overlapEntity)
{
	return;
}
