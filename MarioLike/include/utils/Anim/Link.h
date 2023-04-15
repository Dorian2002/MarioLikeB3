#pragma once
#include "utils/Anim/Animation.h"

class Link
{
public:
	virtual bool CheckCondition() = 0;
	Animation* GetTarget();
private:
	Animation* m_target;
};