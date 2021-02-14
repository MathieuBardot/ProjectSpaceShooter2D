#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <cstdlib>

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

class GameEngine
{
public:
	GameEngine();
	~GameEngine();

	void PlayGame();
	void LaunchGame();

private:
	sf::RenderWindow window;
	sf::Font font;
	sf::Texture playerTex;
	sf::Texture ennemiTex;
	sf::Text score;
	sf::Text gameOver;
	Player player;
	std::vector<Enemy> ennemies;
	int enemySpawnTimer;
};

