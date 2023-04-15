#include "managers/RenderManager.h"

void RenderManager::RenderLevel(sf::RenderTarget& _target)
{
	//if (m_spriteComponent->m_sprite != nullptr)
	//{
	//	Vec2f position = m_spriteComponent->m_transform->m_position;
	//	Vec2f size = m_spriteComponent->m_spriteSize;
	//	m_spriteComponent->m_transform->m_position = position * size;
	//	_target.draw(m_spriteComponent->m_sprite);
	//}
}

void RenderManager::DrawCall(Entity* _entity)
{
	if (std::find(m_toRender.begin(), m_toRender.end(), _entity) == m_toRender.end())
		m_toRender.push_back(_entity);
}