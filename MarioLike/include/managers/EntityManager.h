#pragma once
#include <map>
#include <models/Component.h>
#include <models/Entity.h>
#include <unordered_map>
#include <component/Transform.h>
class toto;
class EntityManager
{
public:
	static EntityManager* GetInstance();
	void Start();
	void Update();
	bool MoveEntity(Transform*);
	bool MoveEntity(Entity*);
    toto* m_toto;
private:
	static EntityManager* m_instance;
	std::vector<Entity*> m_entities;
};

