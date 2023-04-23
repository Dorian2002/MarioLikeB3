#include "models/Level.h"

Level::Level()
{

}

void Level::RenderLevel(sf::RenderTarget& _target, const Vec2f& _tileSize)
{
	//sf::RectangleShape rectangle(sf::Vector2f(120, 50));
	//rectangle.setSize(sf::Vector2f(100, 100));

	Entity* r = new Entity({64,64});

	//r->m_transform->Rotate(100, 100, 35);

	//r->m_transform->Translate(100, 100, 35, 100, 100);

	//r->SetSprite("test");

	//r->m_shape.setFillColor(sf::Color(100, 250, 50));
	//_target.draw(r->m_shape);
	//delete r, r->m_transform;
}
