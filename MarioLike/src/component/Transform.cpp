#include "component/Transform.h"
#include "models/Entity.h"

Transform::Transform(Vec2f v)
{
	m_position = v;
}

void Transform::Rotate(int x1, int y1, int theta)
{
	int x = x1 * cos(theta) + y1 * (-sin(theta));
	int y = x1 * sin(theta) + y1 * cos(theta);
}

void Transform::Translate(int x1, int y1, int theta, int addx, int addy)
{
	int x = x1 * cos(theta) + y1 * (-sin(theta)) + 1 * addx;
	int y = x1 * sin(theta) + y1 * cos(theta) + 1 * addy;
}

void Transform::Scale()
{
}
