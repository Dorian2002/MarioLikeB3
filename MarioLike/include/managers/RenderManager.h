#pragma once
#include "component/SpriteComponent.h"
#include <utils/Vector2.h>
#include <vector>
#include <models/Entity.h>

class RenderManager
{
public:
	static RenderManager* GetInstance();
	static RenderManager* m_instance;
	std::vector<Entity*> m_toRender;
	void RenderLevel(sf::RenderTarget& _target);
	void DrawCall(Entity*);
};

