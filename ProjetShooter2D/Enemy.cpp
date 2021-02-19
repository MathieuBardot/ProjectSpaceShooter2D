#include "Enemy.h"

Enemy::Enemy() : HP(1), HPMax(3), SpawnTimer(0), Speed(1){}

Enemy::Enemy(sf::Texture* tex, sf::Vector2u windowSize)
{
	HPMax = rand() % 3 + 1;
	HP = HPMax;
	SpawnTimer = 0;
	Speed = -4.0f;

	shape.setTexture(*tex);
	shape.setScale(0.08f, 0.08f);
	shape.setPosition(windowSize.x - shape.getGlobalBounds().width, (float)(rand() % (int)(windowSize.y - shape.getGlobalBounds().height)));
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

float Enemy::getSpeed()
{
	return Speed;
}

void Enemy::setSpeed(float vitesse)
{
	Speed = vitesse;
}