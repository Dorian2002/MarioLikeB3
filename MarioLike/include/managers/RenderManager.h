#pragma once
#include "component/SpriteComponent.h"
#include <utils/Vector2.h>
class RenderManager
{
public:
	SpriteComponent* m_spriteComponent;
	void RenderLevel(sf::RenderTarget& _target);
	static void DrawCall();
};

