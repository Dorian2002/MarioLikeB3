#include "component/SpriteComponent.h"

SpriteComponent::SpriteComponent(Entity* root, const std::string& _assetId)
{
	m_sprite = nullptr;
	m_spriteSize = { 16,16 };
	SetSprite(_assetId, {0,0}, m_spriteSize);
	m_root = root;
}

void SpriteComponent::SetSprite(const std::string& _assetId, const Vec2f& _position, const Vec2f& _size)
{
	sf::Texture* texture = AssetManager::GetInstance()->GetTexture(_assetId);

	if (texture != nullptr)
	{
		if (m_sprite != nullptr)
		{
			delete m_sprite;
		}

		m_sprite = new sf::Sprite();
		m_sprite->setTexture(*texture);

		if (_size.x > 0 && _size.y > 0)
		{
			m_sprite->setTextureRect(sf::IntRect(_position.x, _position.y, _size.x, _size.y));
			m_spriteSize = _size;
		}
		else
		{
			m_spriteSize = { (float)texture->getSize().x, (float)texture->getSize().y };
		}
	}
}

void SpriteComponent::UpdateSprite(sf::Texture* texture, int val, bool isLast) {
	m_sprite->setTextureRect(sf::IntRect(val, 0, m_spriteSize.x, m_spriteSize.y));
}
