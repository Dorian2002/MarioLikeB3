#include "managers/RenderManager.h"
#include <models/Entity.h>
#include <vector>
#include <algorithm>

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
	for (DrawCall* call : m_toRender) 
	{
		Vec2f position;
		Vec2f size;
		if (auto* T = call->m_entity->GetComponent<Transform>();T) {
			position = T->m_position;
		}
		if (auto* T = call->m_entity->GetComponent<SpriteComponent>(); T) {
			size = T->m_spriteSize;
			T->m_sprite->setPosition(position * size);//A check, peut TOUT PETER !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			_target.draw(*T->m_sprite);
		}
	}
}

bool RenderManager::compareDrawcallOrder(const DrawCall& dc1, const DrawCall& dc2)
{
	return dc1.m_plan > dc2.m_plan;
}

void RenderManager::AddDrawCall(DrawCall* drawCall)
{
	if (!FindEntity(drawCall->m_entity))
		m_toRender.push_back(drawCall);
}

bool RenderManager::FindEntity(Entity* entity) {
	for (DrawCall* _drawcall : m_toRender) {
		if (_drawcall->m_entity == entity) {
			return true;
		}
	}
	return false;
}