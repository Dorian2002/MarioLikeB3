#pragma once
#include "Entity.h"
class Ennemy : public Entity
{
public:
    virtual bool MoveRight() = 0;
    virtual bool MoveLeft() = 0;
};

class Background
{
};

