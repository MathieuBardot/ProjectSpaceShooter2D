#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Enemy
{
public:
	Enemy(Texture *tex, Vector2u windowSize);
	~Enemy();

	Sprite shape;

	// Getter et Setter
	int getHP();
	void setHP(int hp);
	int getHPMax();
	void setHPMax(int hpmax);

protected:

private:
	int HP;
	int HPMax;
};

