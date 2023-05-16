#pragma once
#include "utils/Rtti.h"
class GameObject : public Rtti
{
public:
	DEFINE_RTTI(GameObject)
	virtual void Start() {};
	virtual void Update(float) {};
	virtual void Destroy() {};
};

