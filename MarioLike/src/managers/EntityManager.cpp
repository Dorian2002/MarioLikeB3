#include <managers/EntityManager.h>
#include <models/Player.h>
#include <models/Boomba.h>
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
	m_player = new Player();
	AddEntity(m_player);
	AddEntity(new Boomba());
	
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
void EntityManager::AddEntity(Entity* entity)
{
	m_entities.push_back(entity);
	auto collider = entity->GetComponent<BoxColliderComponent>();
	if(collider != nullptr)
	{
		if(collider->IsBlocking())
		{
			m_blockCollider.push_back(collider);
		}
		else
		{
			m_overlapCollider.push_back(collider);
		}
	}
}

std::vector<Entity*> EntityManager::GetEntities()
{
	return m_entities;
}

std::vector<BoxColliderComponent*> EntityManager::GetOverlapColliders()
{
	return m_overlapCollider;
}
std::vector<BoxColliderComponent*> EntityManager::GetBlockingColliders()
{
	return m_blockCollider;
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

void EntityManager::DeleteEntity(Entity* entity)
{
	for(auto& e : m_entities )
	{
		if (e == entity)
		{
			if (e->GetComponent<BoxColliderComponent>()->IsBlocking())
			{
				for (auto& c: m_blockCollider)
				{
					if (c == e->GetComponent<BoxColliderComponent>())
					{
						
					}
				}
			}
		}
	}
}

