#pragma once
#include "models/GameObject.h"
#include "models/Entity.h"
#include <utils/Vector2.h>
class Level : public GameObject
{
public:
	Level();
	~Level() = default;
	void RenderLevel(sf::RenderTarget& _target, const Vec2f& _tileSize);
};

