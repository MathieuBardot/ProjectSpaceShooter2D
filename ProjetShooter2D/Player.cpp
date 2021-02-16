#include "Player.h"

Player::Player()
{
	this->setHPMax(15);
	this->setHP(getHPMax());
	this->SpawnTimer = 0;
	this->scoring = 0;
}

Player::Player(sf::Texture *tex)
{
	this->setHPMax(15);
	this->setHP(getHPMax());
	this->SpawnTimer = 0;
	this->scoring = 0;

	this->shape.setTexture(*tex);
	this->shape.setScale(0.3f,0.3f);
}

Player::~Player() {}

// Getter and Setter
int Player::getScoring()
{
	return scoring;
}

void Player::setScoring(int score)
{
	scoring = score;
}

// Player movement
void Player::PlayerMovement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		this->shape.move(0.f, -10.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		this->shape.move(0.f, 10.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		this->shape.move(10.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		this->shape.move(-10.f, 0.f);
}

// Player Collission with the window
void Player::WindowCollision(sf::Vector2u windowSize)
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
void Player::Shooting()
{
	if (this->SpawnTimer < 20)
		this->SpawnTimer++;

	if (sf:: Mouse::isButtonPressed(sf::Mouse::Left) && SpawnTimer >= 20) // Shooting
	{
		this->bullets.push_back(Bullet(this->shape.getPosition()));
		SpawnTimer = 0; //reset timer
	}

	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i].shape.move(20.f, 0.f);
	}
}

// Method for detroy bullets when go out the window
void Player::BulletsOut(sf::Vector2u windowSize)
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