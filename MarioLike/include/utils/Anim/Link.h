#pragma once
#include "utils/Anim/Animation.h"

class Link
{
public:
	virtual bool CheckCondition() = 0;
	Animation* GetTarget();
	Animation* GetOrigin();
private:
	Animation* m_origin;
	Animation* m_target;
};