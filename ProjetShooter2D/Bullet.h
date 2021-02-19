#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
public:
	Bullet(sf::Texture *tex, sf::Vector2f pos);
	~Bullet();

	sf::Sprite shape;
};

