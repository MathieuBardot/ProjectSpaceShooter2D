#include "Player.h"

Player::Player()
{
	this->setHPMax(15);
	this->setHP(getHPMax());
	this->SpawnTimer = 0;
	this->scoring = 0;
}

Player::Player(Texture *tex)
{
	this->setHPMax(15);
	this->setHP(getHPMax());
	this->SpawnTimer = 30;
	/*this->HPMax = 15;
	this->HP = this->HPMax;
	this->ShootTimer = 20;*/
	this->scoring = 0;

	//this->shape.setTexture(*tex);
	this->shape.setTexture(*tex);
	this->shape.setScale(0.3f,0.3f);
}

Player::~Player() {}

// Getter and Setter
/*int Player::getHP()
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

sf::Texture Player::getTex() {
	return *texture;
}

void Player::setTex(sf::Texture* tex)
{
	*texture = *tex;
}*/

int Player::getScoring()
{
	return scoring;
}

void Player::setScoring(int score)
{
	scoring = score;
}

// Player movement
void Player::Movement()
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
}

void Player::MovementBullets()
{
	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i].shape.move(20.f, 0.f);
	}
}

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

//Ennemy Collision with Bullets
void Player::EnemyCollisionWithBullets(std::vector<Enemy> ennemies)
{
	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		//Ennemy Collision with Bullets
		for (size_t j = 0; j < ennemies.size(); j++)
		{
			if (this->bullets[i].shape.getGlobalBounds().intersects(ennemies[j].shape.getGlobalBounds()))
			{
				if (ennemies[j].getHP() <= 1)
				{
					this->setScoring(this->getScoring() + ennemies[j].getHPMax());
					ennemies.erase(ennemies.begin() + j);
				}
				else {
					ennemies[j].setHP(ennemies[j].getHP() - 1);
				}

				this->bullets.erase(this->bullets.begin() + i);
				break;
			}
		}
	}
}