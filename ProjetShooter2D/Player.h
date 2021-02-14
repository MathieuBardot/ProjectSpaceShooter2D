#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Bullet.h"

using namespace sf;

class Player
{
public:
	Player(Texture *tex);
	~Player();

	Sprite shape;
	std::vector<Bullet> bullets;

	// Getter et Setter
	int getHP();
	void setHP(int hp);
	int getHPMax();
	void setHPMax(int hpmax);
	Texture getTex();
	void setTex(Texture* tex);

	void Movement();
	void WindowCollision(Vector2u windowSize);
	void Shooting();
	void MovementBullets();
	void BulletsOut(Vector2u windowSize);

protected:
	int ShootTimer;

private:
	int HP;
	int HPMax;
	Texture *texture;
};

