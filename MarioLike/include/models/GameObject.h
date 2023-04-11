#pragma once
#include "utils/Rtti.h"
class GameObject : public Rtti
{
public:

	virtual void Start() {};
	virtual void Update(float) {};
};

