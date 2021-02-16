#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <cstdlib>
#include <vector>

#include "Player.h"
#include "Enemy.h"

class GameEngine
{
public:
	GameEngine();
	~GameEngine();

	void PlayGame();

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

