#include "Player.h"

Player::Player()
{
	setHPMax(15);
	setHP(getHPMax());
	SpawnTimer = 0;
	scoring = 0;
	setSpeed(10.f);
}

Player::Player(sf::Texture *tex)
{
	setHPMax(15);
	setHP(getHPMax());
	SpawnTimer = 0;
	scoring = 0;
	setSpeed(10.f);

	shape.setTexture(*tex);
	shape.setScale(0.17f,0.17f);
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		shape.move(0.f, - getSpeed()); 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		shape.move(0.f, getSpeed()); 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		shape.move(getSpeed(), 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		shape.move(- getSpeed(), 0.f);
}

// Player Collission with the window
void Player::WindowCollision(sf::Vector2u windowSize)
{
	if (shape.getPosition().x <= 0) //Left
		shape.setPosition(0.f, shape.getPosition().y);
	if (shape.getPosition().x >= windowSize.x - shape.getGlobalBounds().width) //Right
		shape.setPosition(windowSize.x - shape.getGlobalBounds().width, shape.getPosition().y);
	if (shape.getPosition().y <= 0) //Top
		shape.setPosition(shape.getPosition().x, 0.f);
	if (shape.getPosition().y >= windowSize.y - shape.getGlobalBounds().height) //Bottom
		shape.setPosition(shape.getPosition().x, windowSize.y - shape.getGlobalBounds().height);
}

// Player shoot bullets
void Player::Shooting(sf::Texture* tex, sf::Vector2u windowSize)
{
	if (SpawnTimer < 20)
		SpawnTimer++;

	if (sf:: Mouse::isButtonPressed(sf::Mouse::Left) && SpawnTimer >= 20) // Shooting
	{
		bullets.push_back(Bullet(tex, shape.getPosition()));
		SpawnTimer = 0; //reset timer
	}

	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i].shape.move(getSpeed() * 2.0f , 0.f);
		// for detroy bullets when go out the window
		if (bullets[i].shape.getPosition().x > windowSize.x)
		{
			bullets.erase(bullets.begin() + i);
			break;
		}
	}
}