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
	float getSpeed();
	void setSpeed(float vitesse);

private:
	int HP;
	int HPMax;
	float Speed;
};

