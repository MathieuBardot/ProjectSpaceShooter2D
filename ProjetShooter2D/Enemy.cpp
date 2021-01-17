#include "Enemy.h"

Enemy::Enemy(Texture* tex, Vector2u windowSize)
{
	this->HPMax = rand() % 3 + 1;
	this->HP = this->HPMax;

	this->shape.setTexture(*tex);
	this->shape.setScale(0.2f, 0.2f);

	this->shape.setPosition(windowSize.x - this->shape.getGlobalBounds().width, (float)(rand() % (int)(windowSize.y - this->shape.getGlobalBounds().height)));
}

Enemy::~Enemy(){}

int Enemy::getHP()
{
	return HP;
}

void Enemy::setHP(int hp)
{
	HP = hp;
}

int Enemy::getHPMax()
{
	return HPMax;
}

void Enemy::setHPMax(int hpmax)
{
	HPMax = hpmax;
}
