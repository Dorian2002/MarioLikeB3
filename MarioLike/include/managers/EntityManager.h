#pragma once
#include <map>
#include <models/Component.h>
#include <models/Entity.h>
#include <unordered_map>
#include <component/Transform.h>
class Player;
class EntityManager
{
public:
	static EntityManager* GetInstance();
	void Start();
	void Update();
	bool MoveEntity(Entity*);
    Player* m_player;
private:
	static EntityManager* m_instance;
	std::vector<Entity*> m_entities;
};

