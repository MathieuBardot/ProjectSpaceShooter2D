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

	std::vector<Bullet> bullets;

	// Getter et Setter
	int getScoring();
	void setScoring(int score);

	void PlayerMovement();
	void WindowCollision(sf::Vector2u windowSize);
	void Shooting();
	void MovementBullets();
	void BulletsOut(sf::Vector2u windowSize);

private:
	int scoring;
};

