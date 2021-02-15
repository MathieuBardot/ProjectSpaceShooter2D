#include "Bullet.h"

Bullet::Bullet(sf::Vector2f pos)
{
	this->shape.setSize(sf::Vector2f(30.0f, 30.0f));
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setPosition(pos);
}

Bullet::~Bullet(){}