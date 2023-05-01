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
	BoxColliderComponent(Entity*, Vec2f*);
	bool CheckCollisions(Transform*);
private:
	Vec2f* m_size;
};