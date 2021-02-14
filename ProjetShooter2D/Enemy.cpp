#include "Enemy.h"

Enemy::Enemy() : HP(1), HPMax(3), SpawnTimer(0){}

Enemy::Enemy(sf::Texture* tex, sf::Vector2u windowSize)
{
	this->HPMax = rand() % 3 + 1;
	this->HP = this->HPMax;
	this->SpawnTimer = 0;

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

//Enemy get out of the window
void Enemy::EnemyOutWindow(std::vector<Enemy> ennemies)
{
	for (size_t i = 0; i < ennemies.size(); i++)
	{
		if (ennemies[i].shape.getPosition().x <= 0 - ennemies[i].shape.getGlobalBounds().width)
		{
			ennemies.erase(ennemies.begin() + i);
			break;
		}
	}
}

//Enemy collision with Player
void Enemy::CollisionWithPlayer(std::vector<Enemy> ennemies)
{
	/*for (size_t i = 0; i < ennemies.size(); i++)
	{
		//Enemy collision with Player
		if (this->shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
		{
			player.setScoring(player.getScoring() + this->getHPMax());
			ennemies.erase(ennemies.begin() + i);
			player.setHP(player.getHP() - this->getHP());
			//hpPlayer.setSize(Vector2f((float)(player.getHP() * 10), 10.f));
		}
	}*/
}
