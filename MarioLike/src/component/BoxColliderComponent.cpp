#include "component/BoxColliderComponent.h"
#include <component/Transform.h>
#include<managers/LevelManager.h>
#include <component/SpriteComponent.h>

BoxColliderComponent::BoxColliderComponent(Entity* root, Vec2f* size , bool isBlocking)
{
	m_root = root;
	m_size = size;
	m_isBlocking = isBlocking;
}

bool BoxColliderComponent::CheckCollisions()
{
	Vec2f rtp = m_root->GetComponent<Transform>()->GetPosition();
	Vec2f rsp = m_root->GetComponent<SpriteComponent>()->m_spriteSize;
	std::vector<BoxColliderComponent*> colliders = LevelManager::GetInstance()->GetLevel()->m_colliders;
	std::vector<std::vector<Entity*>> map = LevelManager::GetInstance()->GetLevel()->m_map;

	float rootLeft = floor(rtp.x * rsp.x);
	float rootRight = std::round(rtp.x * rsp.x + rsp.x);
	float rootTop = floor(rtp.y * rsp.y);
	float rootBot = std::round(rtp.y * rsp.y + rsp.y);

	for (std::vector<Entity*> l : map) {
		for (Entity* e : l) {
			if (BoxColliderComponent* col = e->GetComponent<BoxColliderComponent>()) {
				if (col->m_isBlocking)
				{
					Vec2f etp = e->GetComponent<Transform>()->GetPosition();
					Vec2f esp = e->GetComponent<SpriteComponent>()->m_spriteSize;
					float posLeft = floor(etp.x * esp.x);
					float posRight = std::round(etp.x * esp.x + esp.x);
					float posTop = floor(etp.y * esp.y);
					float posBot = std::round(etp.y * esp.y + esp.y);
					if (rootRight >= posLeft && rootLeft <= posRight && rootBot >= posTop && rootTop <= posBot) {
						return false;
					}
				}
			}
		}
	}
	return true;
}

bool BoxColliderComponent::CheckCollisions(Vec2f translate)
{
	Vec2f rtp = m_root->GetComponent<Transform>()->GetPosition();
	Vec2f rsp = m_root->GetComponent<SpriteComponent>()->m_spriteSize;
	std::vector<BoxColliderComponent*> colliders = LevelManager::GetInstance()->GetLevel()->m_colliders;
	std::vector<std::vector<Entity*>> map = LevelManager::GetInstance()->GetLevel()->m_map;

	float rootLeft = floor((rtp.x + translate.x) * rsp.x);
	float rootRight = std::round((rtp.x + translate.x) * rsp.x + rsp.x);
	float rootTop = floor((rtp.y + translate.y) * rsp.y);
	float rootBot = std::round((rtp.y + translate.y) * rsp.y + rsp.y);

	for (std::vector<Entity*> l : map) {
		for (Entity* e : l) {
			if (BoxColliderComponent* col = e->GetComponent<BoxColliderComponent>()) {
				if (col->m_isBlocking)
				{
					Vec2f etp = e->GetComponent<Transform>()->GetPosition();
					Vec2f esp = e->GetComponent<SpriteComponent>()->m_spriteSize;
					float posLeft = floor(etp.x * esp.x);
					float posRight = std::round(etp.x * esp.x + esp.x);
					float posTop = floor(etp.y * esp.y);
					float posBot = std::round(etp.y * esp.y + esp.y);
					if (rootRight >= posLeft && rootLeft <= posRight && rootBot >= posTop && rootTop <= posBot) {
						return false;
					}
				}
			}
		}
	}
	return true;
}
