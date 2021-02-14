#include "GameEngine.h"

GameEngine::GameEngine()
{
    this->window.create(sf::VideoMode(800, 600), "Space Shooter 2D");
    this->window.setFramerateLimit(60);

    //Init text
    this->font.loadFromFile("arial.ttf");

    // Init textures
    this->playerTex.loadFromFile("Images/ShipPlayer2.png");
    this->ennemiTex.loadFromFile("Images/EnnemiShip2.png");

    //UI Init
    this->score.setFont(font);
    this->score.setCharacterSize(20);
    this->score.setFillColor(Color::White);
    this->score.setPosition(10.f, 10.f);

    this->gameOver.setFont(font);
    this->gameOver.setCharacterSize(50);
    this->gameOver.setFillColor(Color::Red);
    this->gameOver.setPosition(100.f, (float)(window.getSize().x / 2));
    this->gameOver.setString("GAME OVER !");

    //Player Init
    //this->player(Player(&playerTex));
    Player player(&playerTex);

    //Ennemie Init
    this->enemySpawnTimer = 0;
}

GameEngine::~GameEngine() {};


void GameEngine::PlayGame()
{
    srand(time(NULL));
    // Init Life bar for player
    sf::RectangleShape hpPlayer(Vector2f((float)player.getHPMax() * 10, 10.f));
    hpPlayer.setFillColor(Color::Blue);
    // Init Life bar for enemies
    sf::RectangleShape hpEnemy(Vector2f(100.f, 100.f));
    hpEnemy.setFillColor(Color::Red);

    while (window.isOpen())
    {
        sf::Event event;
        while (this->window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                this->window.close();
        }

        if (this->player.getHP() > 0)
        {
            this->player.Movement();

            //Position for life bar in fornt of the player shape
            hpPlayer.setPosition(this->player.shape.getPosition().x, this->player.shape.getPosition().y - hpPlayer.getGlobalBounds().height);

            this->player.WindowCollision(window.getSize());

            this->player.Shooting();

            this->player.MovementBullets();

            this->player.BulletsOut(window.getSize());

            for (size_t i = 0; i < this->player.bullets.size(); i++)
            {
                //Ennemy Collision with Bullets
                for (size_t j = 0; j < ennemies.size(); j++)
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

            //Enemy
            if (this->enemySpawnTimer < 30)
                this->enemySpawnTimer++;

            if (this->enemySpawnTimer >= 30)
            {
                this->ennemies.push_back(Enemy(&ennemiTex, this->window.getSize()));
                this->enemySpawnTimer = 0; //reset timer
            }

            for (size_t i = 0; i < this->ennemies.size(); i++)
            {
                //Movement
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

        if (this->player.getHP() <= 0)
            this->window.draw(this->gameOver);

        this->window.display();
    }
}

void GameEngine::LaunchGame()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(800, 600), "Space Shooter 2D");
    window.setFramerateLimit(60);

    //Init text
    sf::Font font;
    font.loadFromFile("arial.ttf");

    // Init textures
    sf::Texture playerTex;
    playerTex.loadFromFile("Images/ShipPlayer2.png");

    sf::Texture ennemiTex;
    ennemiTex.loadFromFile("Images/EnnemiShip2.png");

    //UI Init
    sf::Text score;
    score.setFont(font);
    score.setCharacterSize(20);
    score.setFillColor(Color::White);
    score.setPosition(10.f, 10.f);

    sf::Text gameOver;
    gameOver.setFont(font);
    gameOver.setCharacterSize(50);
    gameOver.setFillColor(Color::Red);
    gameOver.setPosition(100.f, (float)(window.getSize().x / 2));
    gameOver.setString("GAME OVER !");

    //Player Init
    Player player(&playerTex);
    // Init Life bar for player
    sf::RectangleShape hpPlayer(Vector2f((float)player.getHPMax() * 10, 10.f));
    hpPlayer.setFillColor(Color::Blue);

    //Ennemie Init
    int enemySpawnTimer = 0;
    std::vector<Enemy> ennemies;
    // Init Life bar for enemies
    sf::RectangleShape hpEnemy(Vector2f(100.f, 100.f));
    hpEnemy.setFillColor(Color::Red);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if (player.getHP() > 0)
        {
            player.Movement();

            //Position for life bar in fornt of the player shape
            hpPlayer.setPosition(player.shape.getPosition().x, player.shape.getPosition().y - hpPlayer.getGlobalBounds().height);

            player.WindowCollision(window.getSize());

            player.Shooting();

            player.MovementBullets();

            player.BulletsOut(window.getSize());

            //player.EnemyCollisionWithBullets(ennemies);

            for (size_t i = 0; i < player.bullets.size(); i++)
            {
                //Ennemy Collision with Bullets
                for (size_t j = 0; j < ennemies.size(); j++)
                {
                    if (player.bullets[i].shape.getGlobalBounds().intersects(ennemies[j].shape.getGlobalBounds()))
                    {
                        if (ennemies[j].getHP() <= 1)
                        {
                            player.setScoring(player.getScoring() + ennemies[j].getHPMax());
                            ennemies.erase(ennemies.begin() + j);
                        }
                        else {
                            ennemies[j].setHP(ennemies[j].getHP() - 1);
                            hpEnemy.setSize(sf::Vector2f((float)(ennemies[j].getHP() * 10), 5.f));
                        }

                        player.bullets.erase(player.bullets.begin() + i);
                        break;
                    }
                }
            }

            //Enemy
            if (enemySpawnTimer < 30)
                enemySpawnTimer++;

            if (enemySpawnTimer >= 30)
            {
                ennemies.push_back(Enemy(&ennemiTex, window.getSize()));
                enemySpawnTimer = 0; //reset timer
            }

            for (size_t i = 0; i < ennemies.size(); i++)
            {
                //Movement
                ennemies[i].shape.move(-4.0f, 0.f);

                //Enemy get out of the window
                if (ennemies[i].shape.getPosition().x <= 0 - ennemies[i].shape.getGlobalBounds().width)
                {
                    ennemies.erase(ennemies.begin() + i);
                    break;
                }

                //Enemy collision with Player
                if (ennemies[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
                {
                    player.setScoring(player.getScoring() + ennemies[i].getHPMax());
                    ennemies.erase(ennemies.begin() + i);
                    player.setHP(player.getHP() - ennemies[i].getHP());
                    hpPlayer.setSize(sf::Vector2f((float)(player.getHP() * 10), 10.f));
                    break;
                }
            }
        }

        //UI Update
        score.setString("Score :" + std::to_string(player.getScoring()));

        //Draw
        window.clear();
        window.draw(player.shape);

        for (size_t i = 0; i < player.bullets.size(); i++)
        {
            window.draw(player.bullets[i].shape);
        }

        for (size_t i = 0; i < ennemies.size(); i++)
        {
            hpEnemy.setSize(sf::Vector2f((float)(ennemies[i].getHPMax() * 10), 5.f));
            hpEnemy.setPosition(ennemies[i].shape.getPosition().x, ennemies[i].shape.getPosition().y - hpEnemy.getGlobalBounds().height);
            window.draw(hpEnemy);
            window.draw(ennemies[i].shape);
        }

        //UI
        window.draw(score);
        window.draw(hpPlayer);

        if (player.getHP() <= 0)
            window.draw(gameOver);

        window.display();
    }
}