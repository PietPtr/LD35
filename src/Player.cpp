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

    if (totalTime.asMilliseconds() - timeHit > 1000)
    {
        timeHit = -1;
        rotation = 0;
    }

    for (int i = 0; i < obstacles.size(); i++)
    {
        if ((lane == obstacles[i].lane || (obstacles[i].size == 2 && lane == obstacles[i].lane + 1) && timeHit == -1)
            && obstacles[i].position > position.y && obstacles[i].position < position.y + 30)
        {
            timeHit = totalTime.asMilliseconds();

        }
    }
}

void Player::draw(DrawData dd, Time totalTime, double speed)
{
    Sprite player;
    player.setPosition(position);
    int frameTime = 200;
    int frame = (totalTime.asMilliseconds() / frameTime) % 3;
    player.setTexture(dd.textures->at(1));
    player.setTextureRect(IntRect((frame) * 120, (int)state * 120, 120, 120));
    if (timeHit == -1 || (timeHit != -1 && totalTime.asMilliseconds() / 150 % 2 == 0))
        dd.window->draw(player);
}
