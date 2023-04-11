#pragma once
#include "models/GameObject.h"
#include "models/Component.h"
#include "component/Transform.h"
#include "managers/AssetManager.h"
#include <utils/Vector2.h>

class SpriteComponent : public GameObject
{
public:
	sf::Sprite* m_sprite;
	Transform* m_transform;
	Vec2f m_spriteSize;
	SpriteComponent();
	~SpriteComponent() = default;
	void SetSprite(const std::string& _assetId, const Vec2f& _position, const Vec2f& _size);
};