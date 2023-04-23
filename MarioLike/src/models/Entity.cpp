#include "models/Entity.h"
#include <managers/AssetManager.h>

void Entity::Start()
{
	for (auto& component : Components) {
		std::cout << " - " << component->GetClassRttiName() << std::endl;
	}
	std::cout << std::endl;
}

Entity::Entity(Vec2f _spriteSize)
{
}