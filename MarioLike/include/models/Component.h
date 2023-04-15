#pragma once
#include "models/GameObject.h"
#include "utils/Rtti.h"
class Component : GameObject
{
public:
	DEFINE_RTTI(Component);
	virtual void Start() override {};
	virtual void Update(float) {};
};

