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

struct
{
	bool operator() (DrawCall* a, DrawCall* b) const { return a->m_plan > b->m_plan; }
} sortRender;

void RenderManager::RenderLevel(sf::RenderTarget& _target)
{
	//sort m_torender
	std::sort(m_toRender.begin(), m_toRender.end(), sortRender);
	for (DrawCall* call : m_toRender) 
	{
		if (call->m_entity == nullptr) {
			remove(m_toRender.begin(), m_toRender.end(), call);
		}
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

void RenderManager::AddDrawCall(DrawCall* drawCall)
{
	if (!FindEntity(drawCall->m_entity))
		m_toRender.push_back(drawCall);
	else
	{
		delete drawCall;
	}
}

bool RenderManager::FindEntity(Entity* entity) {
	for (DrawCall* _drawcall : m_toRender) {
		if (_drawcall->m_entity == entity) {
			return true;
		}
	}
	return false;
}