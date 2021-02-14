#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
public:
	Enemy();
	Enemy(sf::Texture *tex, sf::Vector2u windowSize);
	~Enemy();

	sf::Sprite shape;
	int SpawnTimer;

	// Getter et Setter
	int getHP();
	void setHP(int hp);
	int getHPMax();
	void setHPMax(int hpmax);

	void EnemyOutWindow(std::vector<Enemy> ennemies);
	void CollisionWithPlayer(std::vector<Enemy> ennemies);

private:
	int HP;
	int HPMax;
};

