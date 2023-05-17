#include "component/BoxColliderComponent.h"
#include <component/Transform.h>
#include<managers/LevelManager.h>
#include <component/SpriteComponent.h>

#include "managers/EntityManager.h"

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

	float rootLeft = floor(rtp.x * rsp.x);
	float rootRight = std::round(rtp.x * rsp.x + rsp.x);
	float rootTop = floor(rtp.y * rsp.y);
	float rootBot = std::round(rtp.y * rsp.y + rsp.y);

	for (auto c : EntityManager::GetInstance()->GetBlockingColliders()) {
		Vec2f etp = c->m_root->GetComponent<Transform>()->GetPosition();
		Vec2f esp = c->m_root->GetComponent<SpriteComponent>()->m_spriteSize;
		float posLeft = floor(etp.x * esp.x);
		float posRight = std::round(etp.x * esp.x + esp.x);
		float posTop = floor(etp.y * esp.y);
		float posBot = std::round(etp.y * esp.y + esp.y);
		if (rootRight >= posLeft && rootLeft <= posRight && rootBot >= posTop && rootTop <= posBot) {
			if (c->m_isBlocking)
			{
				m_root->OnCollide(this, c->m_root);
				return false;
			}
		}
	}
	return true;
}

bool BoxColliderComponent::CheckCollisions(Vec2f translate)
{
	Vec2f rtp = m_root->GetComponent<Transform>()->GetPosition();
	Vec2f rsp = m_root->GetComponent<SpriteComponent>()->m_spriteSize;

	float rootLeft = floor((rtp.x + translate.x) * rsp.x);
	float rootRight = std::round((rtp.x + translate.x) * rsp.x + rsp.x);
	float rootTop = floor((rtp.y + translate.y) * rsp.y);
	float rootBot = std::round((rtp.y + translate.y) * rsp.y + rsp.y);

	for (auto c : EntityManager::GetInstance()->GetBlockingColliders()) {
		Vec2f etp = c->m_root->GetComponent<Transform>()->GetPosition();
		Vec2f esp = c->m_root->GetComponent<SpriteComponent>()->m_spriteSize;
		float posLeft = floor(etp.x * esp.x);
		float posRight = std::round(etp.x * esp.x + esp.x);
		float posTop = floor(etp.y * esp.y);
		float posBot = std::round(etp.y * esp.y + esp.y);
		if (rootRight >= posLeft && rootLeft <= posRight && rootBot >= posTop && rootTop <= posBot) {
			if (c->m_isBlocking)
			{
				m_root->OnCollide(this, c->m_root);
				return false;
			}
		}
	}
	return true;
}

bool BoxColliderComponent::IsBlocking()
{
	return m_isBlocking;
}

void BoxColliderComponent::Update(float deltaT)
{
	Vec2f rtp = m_root->GetComponent<Transform>()->GetPosition();
	Vec2f rsp = m_root->GetComponent<SpriteComponent>()->m_spriteSize;

	float rootLeft = floor(rtp.x * rsp.x);
	float rootRight = std::round(rtp.x * rsp.x + rsp.x);
	float rootTop = floor(rtp.y * rsp.y);
	float rootBot = std::round(rtp.y * rsp.y + rsp.y);

	for (auto c : EntityManager::GetInstance()->GetOverlapColliders()) {
		Vec2f etp = c->m_root->GetComponent<Transform>()->GetPosition();
		Vec2f esp = c->m_root->GetComponent<SpriteComponent>()->m_spriteSize;
		float posLeft = floor(etp.x * esp.x);
		float posRight = std::round(etp.x * esp.x + esp.x);
		float posTop = floor(etp.y * esp.y);	
		float posBot = std::round(etp.y * esp.y + esp.y);
		if (rootRight >= posLeft && rootLeft <= posRight && rootBot >= posTop && rootTop <= posBot) {
			if (c != this)
			{
				m_root->OnOverlap(this, c->m_root);
			}
		}
	}
	
}
