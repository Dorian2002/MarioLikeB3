#pragma once
#include <map>
#include <models/Component.h>
#include <models/Entity.h>
#include <unordered_map>
class EntityManager
{
public:
	EntityManager* GetInstance();
	void Start();
private:
	static EntityManager* m_instance;
	std::vector<Entity*> m_entities;
};

