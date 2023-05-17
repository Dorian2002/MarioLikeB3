#pragma once
#include "models/GameObject.h"
class Entity;
class Component : public GameObject
{
public:
	DEFINE_RTTI(Component);
	virtual void Start() override {};
	virtual void Update(float) {};
	Entity* m_root;
	~Component() = default;
};

