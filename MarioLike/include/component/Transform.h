#pragma once
#include "models/GameObject.h"
#include <utils/Vector2.h>
#include "models/Component.h"

class Transform : public Component
{
public:
	DEFINE_RTTI(Transform);
	Transform(Vec2f v);
	~Transform() = default;

	void Rotate(int x1, int y1, int theta);
	void Translate(int x1, int y1, int theta, int addx, int addy);
	void Scale();

	//Vec2f* GetPosition();
	//void SetPosition(Vec2f* _v);
	Vec2f m_position;
};