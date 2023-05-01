#include "component/Transform.h"
#include "models/Entity.h"

Transform::Transform(Entity* root, Vec2f v)
{
	m_position = v;
	m_root = root;
}

void Transform::Rotate(float x1, float y1, int theta)
{
	int x = x1 * cos(theta) + y1 * (-sin(theta));
	int y = x1 * sin(theta) + y1 * cos(theta);
}

Vec2f Transform::Translate(float x1, float y1, int theta, float addx, float addy)
{
	float x = x1 * cos(theta) + y1 * (-sin(theta)) + 1 * addx;
	float y = x1 * sin(theta) + y1 * cos(theta) + 1 * addy;
	return { x,y };
}

void Transform::Scale()
{
}

//Vec2f* Transform::GetPosition()
//{
//	return m_position;
//}
//
//void Transform::SetPosition(Vec2f* _v)
//{
//	m_position = _v;
//}

