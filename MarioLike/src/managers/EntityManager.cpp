#include <managers/EntityManager.h>
#include <models/toto.h>
#include <managers/RenderManager.h>
#include <engine/GameEngine.h>
#include <utils/DrawCall.h>

EntityManager* EntityManager::m_instance = nullptr;

EntityManager* EntityManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new EntityManager();
	}
	return m_instance;
}

void EntityManager::Start()
{
	m_entities.push_back(new toto());
	
	for (Entity* entity : m_entities)
	{
		entity->Start();
		RenderManager::GetInstance()->AddDrawCall(new DrawCall(entity,1));
	}
}

void EntityManager::Update()
{
	float deltaT = GameEngine::GetInstance()->GetDeltaTime();
	for (Entity* entity : m_entities)
	{
		entity->Update(deltaT);
	}
}

bool EntityManager::MoveEntity(Entity* entity)
{
	if (auto col = entity->GetComponent<BoxColliderComponent>()) {
		if (col->CheckCollisions()) {
			RenderManager::GetInstance()->AddDrawCall(new DrawCall(entity, 1));
			return true;
		}
	}
	else {
		RenderManager::GetInstance()->AddDrawCall(new DrawCall(entity, 1));
		return true;
	}
	return false;
}

bool EntityManager::MoveEntity(Entity* entity, Vec2f translate, bool moving)
{
	if (auto col = entity->GetComponent<BoxColliderComponent>()) {
		if (col->CheckCollisions(translate)) {
			if (moving)
			{
				entity->GetComponent<Transform>()->Translate(0, translate.x, translate.y);
			}
			RenderManager::GetInstance()->AddDrawCall(new DrawCall(entity, 1));
			return true;
		}
	}
	else {
		RenderManager::GetInstance()->AddDrawCall(new DrawCall(entity, 1));
		return true;
	}
	return false;
}

