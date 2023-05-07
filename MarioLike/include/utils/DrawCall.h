#pragma once
#include "models/Entity.h"
class DrawCall 
{
public:
	DrawCall(Entity* entity, int plan);
	Entity* m_entity;
	int m_plan;
};