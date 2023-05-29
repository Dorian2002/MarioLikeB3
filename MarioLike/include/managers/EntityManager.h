#pragma once
#include <map>
#include <models/Component.h>
#include <models/Entity.h>
#include <unordered_map>
#include <component/Transform.h>
#include "component/BoxColliderComponent.h"
class Player;
class EntityManager
{
public:
	static EntityManager* GetInstance();
	void Start();
	void Update();
	~EntityManager();
	void AddEntity(Entity* entity);
    Player* m_player;
	bool MoveEntity(Entity*, Vec2f translate = { 0,0 }, bool moving = true);
	std::vector<Entity*> GetEntities();
	std::vector<BoxColliderComponent*> GetOverlapColliders();
	std::vector<BoxColliderComponent*> GetBlockingColliders();
	void DeleteEntity(Entity* entity);
	void DeferDeleteEntity(Entity* entity);
private:
	static EntityManager* m_instance;
	std::vector<Entity*> m_entitiesToDelete;
	std::vector<Entity*> m_entities;
	std::vector<BoxColliderComponent*> m_overlapCollider;
	std::vector<BoxColliderComponent*> m_blockCollider;
};

