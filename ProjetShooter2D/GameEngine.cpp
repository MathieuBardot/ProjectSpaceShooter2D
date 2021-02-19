#include "GameEngine.h"

GameEngine::GameEngine()
{
    //Init window for game
    window.create(sf::VideoMode(900, 700), "Space Shooter 2D");
    window.setFramerateLimit(60);

    //Init text
    font.loadFromFile("arial.ttf");

    // Init textures
    playerTex.loadFromFile("Images/goodship.png");
    ennemiTex.loadFromFile("Images/badship.png");
    missileTex.loadFromFile("Images/Missile.jpg");

    //UI Score Init
    score.setFont(font);
    score.setCharacterSize(20);
    score.setFillColor(sf::Color::White);
    score.setPosition(10.f, 10.f);

    //UI text gameOvet Init
    gameOver.setFont(font);
    gameOver.setCharacterSize(50);
    gameOver.setFillColor(sf::Color::Red);
    gameOver.setPosition(100.f, (float)(window.getSize().x / 2));
    gameOver.setString("GAME OVER !");

    //Player Init
    Player playerOne(&playerTex);
    player = playerOne;

    //Spawn Ennemie Init
    enemySpawnTimer = 0;
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
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (player.getHP() > 0)
        {
            player.PlayerMovement();

            //Position for life bar in fornt of the player shape
            hpPlayer.setPosition(player.shape.getPosition().x, player.shape.getPosition().y - hpPlayer.getGlobalBounds().height);

            player.WindowCollision(window.getSize());

            player.Shooting(&missileTex, window.getSize());

            //Enemy
            if (enemySpawnTimer < 30)
                enemySpawnTimer++;

            if (enemySpawnTimer >= 30)
            {
                ennemies.push_back(Enemy(&ennemiTex, window.getSize()));
                enemySpawnTimer = 0; //reset timer
            }

            //Ennemy Collision with Bullets
            for (size_t i = 0; i < player.bullets.size(); i++)
            {
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

            for (size_t i = 0; i < ennemies.size(); i++)
            {
                //Enemy Movement
                ennemies[i].shape.move(ennemies[i].getSpeed(), 0.f);
                if (player.getScoring() > 50)
                {
                     ennemies[i].shape.move(ennemies[i].getSpeed() * (0.03*player.getScoring()), 0.f);
                }

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
                    //Avoid a player with Life bar negatif
                    if (player.getHP() < 0)
                    {
                        player.setHP(0);
                    }
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

        //Condition End Game
        if (player.getHP() <= 0)
            window.draw(gameOver);

        window.display();
    }
}