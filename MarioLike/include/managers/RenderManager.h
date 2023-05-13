#pragma once
#include "component/SpriteComponent.h"
#include <utils/Vector2.h>
#include <vector>
#include <models/Entity.h>
#include <utils/DrawCall.h>

class RenderManager
{
public:
	static RenderManager* GetInstance();
	static RenderManager* m_instance;
	bool compareDrawcallOrder(const DrawCall& dc1, const DrawCall& dc2);
	std::vector<DrawCall*> m_toRender;
	void RenderLevel(sf::RenderTarget& _target);
	void AddDrawCall(DrawCall*);
	bool FindEntity(Entity* entity);
};

