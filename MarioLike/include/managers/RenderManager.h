#pragma once
#include "component/SpriteComponent.h"
#include <utils/Vector2.h>
#include <vector>
class RenderManager
{
public:
	std::vector<Entity*> m_toRender;
	void RenderLevel(sf::RenderTarget& _target);
	void DrawCall(Entity*);
};

