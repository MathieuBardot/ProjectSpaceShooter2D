#include "Player.h"

Player::Player(Texture *tex)
{
	this->HPMax = 15;
	this->HP = this->HPMax;
	this->texture = tex;

	this->shape.setTexture(*texture);
	this->shape.setScale(0.5f,0.5f);

	//this->shape.setRotation(90.f);
	//this->shape.setPosition(0.f, 0.f);

}

Player::~Player() {}

int Player::getHP()
{
	return HP;
}

void Player::setHP(int hp)
{
	HP = hp;
}

int Player::getHPMax()
{
	return HPMax;
}

void Player::setHPMax(int hpmax)
{
	HPMax = hpmax;
}

Texture Player::getTex() {
	return *texture;
}

void Player::setTex(Texture* tex)
{
	*texture = *tex;
}
/*
Sprite Player::getShape()
{
	return shape1;
}

void Player::setShape(Sprite shap)
{
	shape1 = shap;
}

std::vector<Bullet> Player::getBullet()
{
	return bullets;
}

void Player::setBullet(std::vector<Bullet> bull)
{
	bullets = bull;
}*/
