#pragma once
#include <utils/Vector2.h>
#include "models/Component.h"

class Transform : public Component
{
public:
	DEFINE_RTTI(Transform);
	Transform(Entity* root, Vec2f v);
	~Transform() = default;

	void Rotate(float x1, float y1, int theta);
	Vec2f Translate(float x1, float y1, int theta, float addx, float addy);
	void Translate(int theta, float addx, float addy);
	void Scale();

	Vec2f GetPosition();
	void SetPosition(Vec2f _v);
	Vec2f m_position;
};