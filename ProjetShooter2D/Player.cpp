#include "Player.h"

Player::Player(Texture *tex)
{
	this->HPMax = 15;
	this->HP = this->HPMax;

	this->ShootTimer = 20;

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

// Player movement
void Player::Movement()
{
	if (Keyboard::isKeyPressed(Keyboard::Up))
		this->shape.move(0.f, -10.f);
	if (Keyboard::isKeyPressed(Keyboard::Down))
		this->shape.move(0.f, 10.f);
	if (Keyboard::isKeyPressed(Keyboard::Right))
		this->shape.move(10.f, 0.f);
	if (Keyboard::isKeyPressed(Keyboard::Left))
		this->shape.move(-10.f, 0.f);
}

// Player Collission with the window
void Player::WindowCollision(Vector2u windowSize)
{
	if (this->shape.getPosition().x <= 0) //Left
		this->shape.setPosition(0.f, this->shape.getPosition().y);
	if (this->shape.getPosition().x >= windowSize.x - this->shape.getGlobalBounds().width) //Right
		this->shape.setPosition(windowSize.x - this->shape.getGlobalBounds().width, this->shape.getPosition().y);
	if (this->shape.getPosition().y <= 0) //Top
		this->shape.setPosition(this->shape.getPosition().x, 0.f);
	if (this->shape.getPosition().y >= windowSize.y - this->shape.getGlobalBounds().height) //Bottom
		this->shape.setPosition(this->shape.getPosition().x, windowSize.y - this->shape.getGlobalBounds().height);
}

// Player shoot bullets
void Player::Shooting(Texture* bulletTex)
{
	if (this->ShootTimer < 20)
		this->ShootTimer++;

	if (Mouse::isButtonPressed(Mouse::Left) && ShootTimer >= 20) // Shooting
	{
		this->bullets.push_back(Bullet(bulletTex, this->shape.getPosition()));
		ShootTimer = 0; //reset timer
	}
}

void Player::MovementBullets()
{
	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i].shape.move(20.f, 0.f);
	}
}

void Player::BulletsOut(Vector2u windowSize)
{
	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		if (this->bullets[i].shape.getPosition().x > windowSize.x)
		{
			this->bullets.erase(this->bullets.begin() + i);
			break;
		}
	}
}