#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Enemy.h"
#include "Bullet.h"

class Player : public Enemy
{
public:
	Player();
	Player(sf::Texture *tex);
	~Player();

	//sf::Sprite shape;
	std::vector<Bullet> bullets;
	//int SpawnTimer;

	// Getter et Setter
	/*int getHP();
	void setHP(int hp);
	int getHPMax();
	void setHPMax(int hpmax);
	sf::Texture getTex();
	void setTex(sf::Texture* tex);*/
	int getScoring();
	void setScoring(int score);

	void Movement();
	void WindowCollision(sf::Vector2u windowSize);
	void Shooting();
	void MovementBullets();
	void BulletsOut(sf::Vector2u windowSize);

	void EnemyCollisionWithBullets(std::vector<Enemy> ennemies);

private:
	/*int HP;
	int HPMax;
	sf::Texture *texture;*/
	int scoring;
};

