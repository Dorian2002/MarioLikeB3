#pragma once
#include "models/Component.h"
#include <iostream>
#include "utils/Rtti.h"
class TestComponent : public Component
{
public:
	DEFINE_RTTI(TestComponent);
	void Update(float) override {
		
	}
	void Start() override{
		
	}
};