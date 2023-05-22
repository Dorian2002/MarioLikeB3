#pragma once
#pragma once
#include "models/Component.h"
#include <vector>
#include "utils/Anim/Animation.h"
#include "utils/Anim/Link.h"
#include <utils/Vector2.h>
#include <component/Transform.h>

class BoxColliderComponent : public Component
{
public:
	DEFINE_RTTI(BoxColliderComponent)
	BoxColliderComponent(Entity*, Vec2f*, bool isBlocking = true);
	bool CheckCollisions(Vec2f translate);
	bool IsBlocking();
	void Update(float) override;
private:
	Vec2f* m_size;
	bool m_isBlocking;
};