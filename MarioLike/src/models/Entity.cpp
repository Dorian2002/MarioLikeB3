#include "models/Entity.h"
#include <managers/AssetManager.h>

Entity::Entity(Vec2f _spriteSize)
{
	m_transform = new Transform({0,0});
	m_spriteSize = _spriteSize;
}