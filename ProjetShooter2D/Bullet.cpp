#include "Bullet.h"

Bullet::Bullet(sf::Texture *tex, sf::Vector2f pos)
{
	shape.setTexture(*tex);
	shape.setScale(0.1f, 0.1f);
	shape.setPosition(pos);
}

Bullet::~Bullet(){}