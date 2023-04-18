#pragma once
#include "models/GameObject.h"
#include "models/Component.h"
#include "component/Transform.h"
#include "managers/AssetManager.h"
#include <utils/Vector2.h>

class SpriteComponent : public Component
{
public:
	DEFINE_RTTI(SpriteComponent);
	sf::Sprite* m_sprite;
	Vec2f m_spriteSize;
	SpriteComponent(const std::string&);
	~SpriteComponent() = default;
	void SetSprite(const std::string& _assetId, const Vec2f& _position, const Vec2f& _size);
};