#include "GameEngine.h"

GameEngine::GameEngine()
{
    //Init window for game
    this->window.create(sf::VideoMode(800, 600), "Space Shooter 2D");
    this->window.setFramerateLimit(60);

    //Init text
    this->font.loadFromFile("arial.ttf");

    // Init textures
    this->playerTex.loadFromFile("Images/ShipPlayer2.png");
    this->ennemiTex.loadFromFile("Images/EnnemiShip2.png");

    //UI Score Init
    this->score.setFont(font);
    this->score.setCharacterSize(20);
    this->score.setFillColor(sf::Color::White);
    this->score.setPosition(10.f, 10.f);

    //UI text gameOvet Init
    this->gameOver.setFont(font);
    this->gameOver.setCharacterSize(50);
    this->gameOver.setFillColor(sf::Color::Red);
    this->gameOver.setPosition(100.f, (float)(window.getSize().x / 2));
    this->gameOver.setString("GAME OVER !");

    //Player Init
    Player playerOne(&playerTex);
    this->player = playerOne;

    //Spawn Ennemie Init
    this->enemySpawnTimer = 0;
}

GameEngine::~GameEngine() {};

// Method to start and play a game
void GameEngine::PlayGame()
{
    srand(time(NULL));
    // Init Life bar for player
    sf::RectangleShape hpPlayer(sf:: Vector2f((float)player.getHPMax() * 10, 10.f));
    hpPlayer.setFillColor(sf::Color::Blue);
    // Init Life bar for enemies
    sf::RectangleShape hpEnemy;
    hpEnemy.setFillColor(sf::Color::Red);

    while (window.isOpen())
    {
        sf::Event event;
        while (this->window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                this->window.close();
        }

        if (this->player.getHP() > 0)
        {
            this->player.PlayerMovement();

            //Position for life bar in fornt of the player shape
            hpPlayer.setPosition(this->player.shape.getPosition().x, this->player.shape.getPosition().y - hpPlayer.getGlobalBounds().height);

            this->player.WindowCollision(this->window.getSize());

            this->player.Shooting();

            this->player.MovementBullets();

            this->player.BulletsOut(this->window.getSize());

            //Enemy
            if (this->enemySpawnTimer < 30)
                this->enemySpawnTimer++;

            if (this->enemySpawnTimer >= 30)
            {
                this->ennemies.push_back(Enemy(&ennemiTex, this->window.getSize()));
                this->enemySpawnTimer = 0; //reset timer
            }

            //Ennemy Collision with Bullets
            for (size_t i = 0; i < this->player.bullets.size(); i++)
            {
                for (size_t j = 0; j < this->ennemies.size(); j++)
                {
                    if (this->player.bullets[i].shape.getGlobalBounds().intersects(this->ennemies[j].shape.getGlobalBounds()))
                    {
                        if (this->ennemies[j].getHP() <= 1)
                        {
                            this->player.setScoring(this->player.getScoring() + this->ennemies[j].getHPMax());
                            this->ennemies.erase(this->ennemies.begin() + j);
                        }
                        else {
                            this->ennemies[j].setHP(this->ennemies[j].getHP() - 1);
                            hpEnemy.setSize(sf::Vector2f((float)(this->ennemies[j].getHP() * 10), 5.f));
                        }

                        this->player.bullets.erase(this->player.bullets.begin() + i);
                        break;
                    }
                }
            }

            for (size_t i = 0; i < this->ennemies.size(); i++)
            {
                //Enemy Movement
                this->ennemies[i].shape.move(-4.0f, 0.f);

                //Enemy get out of the window
                if (this->ennemies[i].shape.getPosition().x <= 0 - this->ennemies[i].shape.getGlobalBounds().width)
                {
                    this->ennemies.erase(this->ennemies.begin() + i);
                    break;
                }

                //Enemy collision with Player
                if (this->ennemies[i].shape.getGlobalBounds().intersects(this->player.shape.getGlobalBounds()))
                {
                    this->player.setScoring(this->player.getScoring() + this->ennemies[i].getHPMax());
                    this->ennemies.erase(this->ennemies.begin() + i);
                    this->player.setHP(this->player.getHP() - this->ennemies[i].getHP());
                    //Avoid a player Life bar negatif
                    if (this->player.getHP() < 0)
                    {
                        this->player.setHP(0);
                    }
                    hpPlayer.setSize(sf::Vector2f((float)(this->player.getHP() * 10), 10.f));
                    break;
                }
            }
        }

        //UI Update
        this->score.setString("Score :" + std::to_string(this->player.getScoring()));

        //Draw
        this->window.clear();
        this->window.draw(this->player.shape);

        for (size_t i = 0; i < this->player.bullets.size(); i++)
        {
            this->window.draw(this->player.bullets[i].shape);
        }

        for (size_t i = 0; i < this->ennemies.size(); i++)
        {
            hpEnemy.setSize(sf::Vector2f((float)(this->ennemies[i].getHPMax() * 10), 5.f));
            hpEnemy.setPosition(this->ennemies[i].shape.getPosition().x, this->ennemies[i].shape.getPosition().y - hpEnemy.getGlobalBounds().height);
            this->window.draw(hpEnemy);
            this->window.draw(this->ennemies[i].shape);
        }

        //UI
        this->window.draw(this->score);
        this->window.draw(hpPlayer);

        //Condition End Game
        if (this->player.getHP() <= 0)
            this->window.draw(this->gameOver);

        this->window.display();
    }
}