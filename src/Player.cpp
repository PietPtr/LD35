#include "Player.h"
#include <iostream>

using namespace sf;

Player::Player()
{
    //ctor
}

void Player::update(double dt, Time totalTime, std::vector<Obstacle> obstacles)
{
    const int HORIZONTAL_SPEED = 1200;
    const int ROTATIONAL_SPEED = 360;

    if ((int)biome != (int)state && wrongForm == -1)
        wrongForm = totalTime.asMilliseconds();
    else if ((int)biome == (int)state)
        wrongForm = -1;

    if (wrongForm == -1)
    {
        if (wasLeftpressed)
        {
            lane--;
            lanechangeTime = totalTime;
        }
        if (wasRightpressed)
        {
            lane++;
            lanechangeTime = totalTime;
        }

        lane = lane > 2 ? 2 : lane;
        lane = lane < 0 ? 0 : lane;

        position.x = (lane+1) * 120;

        wasRightpressed = false;
        wasLeftpressed = false;
        rotation = 0;
    }
    else
    {
        rotation += ROTATIONAL_SPEED * dt;
        if (totalTime.asMilliseconds() - wrongForm > 1000)
        {
            lives--;
            wrongForm = totalTime.asMilliseconds();
        }
    }

    if (totalTime.asMilliseconds() - timeHit > 1000)
    {
        timeHit = -1;
    }

    for (int i = 0; i < obstacles.size(); i++)
    {
        if ((lane == obstacles[i].lane || (obstacles[i].size == 2 && lane == obstacles[i].lane + 1)) && timeHit == -1
            && obstacles[i].position > position.y && obstacles[i].position < position.y + 30)
        {
            timeHit = totalTime.asMilliseconds();
            lives--;
            std::cout << "Hit.\n";
        }
    }
}

void Player::draw(DrawData dd, Time totalTime, double speed)
{
    Sprite player;
    player.setPosition(position + Vector2f(60, 60));
    int frameTime = 200;
    int frame = (totalTime.asMilliseconds() / frameTime) % 4;
    player.setTexture(dd.textures->at(1));
    player.setTextureRect(IntRect((frame) * 120, (int)state * 120, 120, 120));
    player.setOrigin(60, 60);
    player.setRotation(rotation);
    if (timeHit == -1 || (timeHit != -1 && totalTime.asMilliseconds() / 150 % 2 == 0))
        dd.window->draw(player);


    for (int i = 0; i < lives; i++)
    {
        Sprite life;
        life.setTexture(dd.textures->at(4));
        life.setPosition(i * 60, 0);
        dd.window->draw(life);
    }
}





