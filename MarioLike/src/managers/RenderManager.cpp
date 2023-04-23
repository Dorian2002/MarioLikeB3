#include "managers/RenderManager.h"
#include <models/Entity.h>
#include <vector>

RenderManager* RenderManager::m_instance = nullptr;
RenderManager* RenderManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new RenderManager();
	}
	return m_instance;
}

void RenderManager::RenderLevel(sf::RenderTarget& _target)
{
	for (Entity* entity : m_toRender) 
	{
		Vec2f position;
		Vec2f size;
		if (auto* T = entity->GetComponent<Transform>();T) {
			position = T->m_position;
		}
		if (auto* T = entity->GetComponent<SpriteComponent>(); T) {
			size = T->m_spriteSize;
			position *= size;//A check, peut TOUT PETER !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			_target.draw(*T->m_sprite);
		}
	}
	//Vec2f position = m_spriteComponent->m_transform->m_position;
	//Vec2f size = m_spriteComponent->m_spriteSize;
	//m_spriteComponent->m_transform->m_position = position * size;
	//_target.draw(m_spriteComponent->m_sprite);
}

void RenderManager::DrawCall(Entity* _entity)
{
	if (std::find(m_toRender.begin(), m_toRender.end(), _entity) == m_toRender.end())
		m_toRender.push_back(_entity);
}