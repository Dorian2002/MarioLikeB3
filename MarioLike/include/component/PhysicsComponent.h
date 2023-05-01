#pragma once
#include "models/Component.h"
#include <vector>
#include "utils/Anim/Animation.h"
#include "utils/Anim/Link.h"

class PhysicsComponent : public Component
{
public:
	DEFINE_RTTI(PhysicsComponent)
	PhysicsComponent(Entity*, bool);
	void Update(float) override;
	void Start() override;
	bool GetIsKinematic();
	void SetIsKinematic(bool);
private:
	bool m_isKinematic;
};
