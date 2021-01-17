#include <SFML/Graphics.hpp>
#include <math.h>
#include <cstdlib>

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

using namespace sf;

int main()
{
    srand(time(NULL));
    RenderWindow window(sf::VideoMode(800, 600), "Space Shooter");
    window.setFramerateLimit(60);

    //Init text
    sf::Font font;
    font.loadFromFile("arial.ttf");
    /*if (!font.loadFromFile("arial.ttf"))
        return EXIT_FAILURE;*/

    // Init textures
    Texture playerTex;
    playerTex.loadFromFile("Images/ShipPlayer.jpg");

    Texture ennemiTex;
    ennemiTex.loadFromFile("Images/EnnemiShip.jpg");

    Texture bulletTex;
    bulletTex.loadFromFile("Images/Missile2.jpg");
    
    //UI Init
    Text score;
    score.setFont(font);
    score.setCharacterSize(20);
    score.setFillColor(Color::Black);
    score.setPosition(10.f, 10.f);

    Text gameOver;
    gameOver.setFont(font);
    gameOver.setCharacterSize(50);
    gameOver.setFillColor(Color::Red);
    gameOver.setPosition(100.f, (float)(window.getSize().y /2));
    gameOver.setString("GAME OVER !");

    //Player Init
    Player player(&playerTex);
    int ShootTimer = 20;
    int scoring = 0;

    RectangleShape hpPlayer(Vector2f((float)player.getHPMax()*10,10.f));
    hpPlayer.setFillColor(Color::Blue);

    /*Text hpText;
    hpText.setFont(font);
    hpText.setCharacterSize(12);
    hpText.setFillColor(Color::Black);*/

    //Ennemie Init
    int enemySpawnTimer = 0;
    std::vector<Enemy> ennemies;
   
    RectangleShape hpEnemy(Vector2f(100.f, 100.f));

    /*Text ehpText;
    ehpText.setFont(font);
    ehpText.setCharacterSize(12);
    ehpText.setFillColor(Color::Black);*/

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if (player.getHP() > 0)
        {
            //Player movement
            if (Keyboard::isKeyPressed(Keyboard::Up))
                player.shape.move(0.f, -10.f);
            if (Keyboard::isKeyPressed(Keyboard::Down))
                player.shape.move(0.f, 10.f);
            if (Keyboard::isKeyPressed(Keyboard::Right))
                player.shape.move(10.f, 0.f);
            if (Keyboard::isKeyPressed(Keyboard::Left))
                player.shape.move(-10.f, 0.f);

            hpPlayer.setPosition(player.shape.getPosition().x, player.shape.getPosition().y - hpPlayer.getGlobalBounds().height);

            /*hpText.setPosition(player.shape.getPosition().x, player.shape.getPosition().y - hpText.getGlobalBounds().height);
            hpText.setString(std::to_string(player.HP) + "/" + std::to_string(player.HPMax));*/

            //Collision with Window for Player
            if (player.shape.getPosition().x <= 0) //Left
                player.shape.setPosition(0.f, player.shape.getPosition().y);
            if (player.shape.getPosition().x >= window.getSize().x - player.shape.getGlobalBounds().width) //Right
                player.shape.setPosition(window.getSize().x - player.shape.getGlobalBounds().width, player.shape.getPosition().y);
            if (player.shape.getPosition().y <= 0) //Top
                player.shape.setPosition(player.shape.getPosition().x, 0.f);
            if (player.shape.getPosition().y >= window.getSize().y - player.shape.getGlobalBounds().height) //Bottom
                player.shape.setPosition(player.shape.getPosition().x, window.getSize().y - player.shape.getGlobalBounds().height);

            //Update
            if (ShootTimer < 20)
                ShootTimer++;

            if (Mouse::isButtonPressed(Mouse::Left) && ShootTimer >= 20) // Shooting
            {
                player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
                ShootTimer = 0; //reset timer
            }


            //Bullets out of window
            for (size_t i = 0; i < player.bullets.size(); i++)
            {
                //Move Bullets 
                player.bullets[i].shape.move(20.f, 0.f);

                //Case Bullets get out of the window
                if (player.bullets[i].shape.getPosition().x > window.getSize().x)
                {
                    player.bullets.erase(player.bullets.begin() + i);
                    break;
                }

                //Ennemy Collision with Bullets
                for (size_t j = 0; j < ennemies.size(); j++)
                {
                    if (player.bullets[i].shape.getGlobalBounds().intersects(ennemies[j].shape.getGlobalBounds()))
                    {
                        if (ennemies[j].getHP() <= 1)
                        {
                            scoring += ennemies[j].getHPMax();
                            ennemies.erase(ennemies.begin() + j);
                        }
                        else {
                            ennemies[j].setHP(ennemies[j].getHP() - 1);
                            hpEnemy.setSize(Vector2f((float)(ennemies[j].getHP() *10), 5.f));
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
                    ennemies.erase(ennemies.begin() + i);
                    player.setHP(player.getHP() - ennemies[i].getHP());
                    hpPlayer.setSize(Vector2f((float)(player.getHP()*10),10.f));
                    break;
                }
            }
        }

        //UI Update
        score.setString("Score :" + std::to_string(scoring));

        //Draw
        window.clear();
        window.draw(player.shape);

        for (size_t i = 0; i < player.bullets.size(); i++)
        {
            window.draw(player.bullets[i].shape);
        }

        for (size_t i = 0; i <ennemies.size(); i++)
        {
            hpEnemy.setSize(Vector2f((float)(ennemies[i].getHPMax()*10), 5.f));
            hpEnemy.setFillColor(Color::Red);
            hpEnemy.setPosition(ennemies[i].shape.getPosition().x, ennemies[i].shape.getPosition().y - hpEnemy.getGlobalBounds().height);

            /*ehpText.setString(std::to_string(ennemies[i].Hp) + "/" + std::to_string(ennemies[i].HPMax));
            ehpText.setPosition(ennemies[i].shape.getPosition().x, ennemies[i].shape.getPosition().y - ehpText.getGlobalBounds().height);
            window.draw(ehpText);*/

            window.draw(hpEnemy);
            window.draw(ennemies[i].shape);
        }

        //UI
        window.draw(score);
        //window.draw(hpText);
        window.draw(hpPlayer);

        if (player.getHP() <= 0)
            window.draw(gameOver);

        window.display();
    }

    return 0;
}