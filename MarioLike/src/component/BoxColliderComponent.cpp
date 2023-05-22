#include "component/BoxColliderComponent.h"
#include <component/Transform.h>
#include<managers/LevelManager.h>
#include <component/SpriteComponent.h>

#include "managers/EntityManager.h"


#define GetTransform() m_root->GetComponent<Transform>()
#define GetSprite() m_root->GetComponent<SpriteComponent>()

BoxColliderComponent::BoxColliderComponent(Entity* root, Vec2f* size , bool isBlocking)
{
	m_root = root;
	m_size = size;
	m_isBlocking = isBlocking;
}

bool BoxColliderComponent::CheckCollisions(Vec2f translate)
{
	Vec2f rtp = GetTransform()->GetPosition();
	Vec2f rsp = GetSprite()->m_spriteSize;

	float rootLeft = floor((rtp.x + translate.x) * 16) + .1f;
	float rootRight = std::round((rtp.x + translate.x) * 16 + rsp.x) - .05f;
	float rootTop = floor((rtp.y + translate.y) * 16);
	float rootBot = std::round((rtp.y + translate.y) * 16 + rsp.y);

	for (auto c : EntityManager::GetInstance()->GetBlockingColliders()) {
		Vec2f etp = c->GetTransform()->GetPosition();
		Vec2f esp = c->GetSprite()->m_spriteSize;
		float posLeft = floor(etp.x * 16);
		float posRight = std::round(etp.x * 16 + esp.x);
		float posTop = floor(etp.y * 16);
		float posBot = std::round(etp.y * 16 + esp.y);
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
	Vec2f rtp = GetTransform()->GetPosition();
	Vec2f rsp = GetSprite()->m_spriteSize;

	float rootLeft = floor(rtp.x * 16);
	float rootRight = std::round(rtp.x * 16 + rsp.x);
	float rootTop = floor(rtp.y * 16);
	float rootBot = std::round(rtp.y * 16 + rsp.y);

	for (auto c : EntityManager::GetInstance()->GetOverlapColliders()) {
		Vec2f etp = c->GetTransform()->GetPosition();
		Vec2f esp = c->GetSprite()->m_spriteSize;
		float posLeft = floor(etp.x * 16);
		float posRight = std::round(etp.x * 16 + esp.x);
		float posTop = floor(etp.y * 16);	
		float posBot = std::round(etp.y * 16 + esp.y);
		if (rootRight >= posLeft && rootLeft <= posRight && rootBot >= posTop && rootTop <= posBot) {
			if (c != this)
			{
				m_root->OnOverlap(this, c->m_root);
			}
		}
	}
	
}
