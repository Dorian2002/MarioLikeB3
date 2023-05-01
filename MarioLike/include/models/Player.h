#pragma once
#include "Entity.h"
class Player : public Entity, public Rtti
{
public:
	DEFINE_RTTI(Player)
	void Jump();
	void Move();
	void CountCoin();
};

