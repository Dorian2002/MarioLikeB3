#include "./engine/EntityManager.h"
#include <models/toto.h>

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
	}
}

