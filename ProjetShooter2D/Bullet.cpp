#include "Bullet.h"

Bullet::Bullet(Vector2f pos)
{
	this->shape.setSize(Vector2f(30.0f, 30.0f));
	this->shape.setFillColor(Color::Green);
	this->shape.setPosition(pos);
}

Bullet::~Bullet(){}