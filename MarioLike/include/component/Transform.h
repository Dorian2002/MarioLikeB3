#pragma once
#include "models/GameObject.h"
#include <utils/Vector2.h>

class Entity;

class Transform : public GameObject
{
public:
	Transform(Vec2f v);
	~Transform() = default;
	void Rotate(int x1, int y1, int theta);
	void Translate(int x1, int y1, int theta, int addx, int addy);
	void Scale();
	Vec2f m_position;
};