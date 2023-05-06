#pragma once
#include "models/Component.h"
#include "component/Transform.h"
#include "managers/AssetManager.h"
#include "managers/RenderManager.h"
#include <utils/Vector2.h>

class SpriteComponent : public Component
{
public:
	DEFINE_RTTI(SpriteComponent);
	sf::Sprite* m_sprite;
	Vec2f m_spriteSize;
	SpriteComponent(Entity*, const std::string&, const Vec2f& _size = {16,16});
	~SpriteComponent() = default;
	void SetSprite(const std::string& _assetId, const Vec2f& _position, const Vec2f& _size);
};