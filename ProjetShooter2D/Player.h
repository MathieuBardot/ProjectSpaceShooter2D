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
	/*Sprite getShape();
	void setShape(Sprite shap);
	std::vector<Bullet> getBullet();
	void setBullet(std::vector<Bullet> bull);*/

protected:

private:
	int HP;
	int HPMax;
	Texture *texture;
	//Sprite shape1;

};

