#include "component/BoxColliderComponent.h"
#include <component/Transform.h>
#include<managers/LevelManager.h>

BoxColliderComponent::BoxColliderComponent(Entity* root, Vec2f* size)
{
	m_root = root;
	m_size = size;
}

bool BoxColliderComponent::CheckCollisions(Transform* transform)
{
	std::vector<std::vector<Entity*>> map = LevelManager::GetInstance()->GetLevel()->m_map;
	if (map.at(transform->m_position.y+1).at(transform->m_position.x)->GetClassRttiName() == "Block") {
		return false;
	}
	return true;
}