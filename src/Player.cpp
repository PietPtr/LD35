#include "Player.h"
#include <iostream>

using namespace sf;

Player::Player()
{
    //ctor
}

void Player::update(double dt, Time totalTime)
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
}

void Player::draw(DrawData dd, Time totalTime, double speed)
{
    Sprite player;
    player.setPosition(position);
    int frameTime = 200;
    int frame = (totalTime.asMilliseconds() / frameTime) % 3;
    player.setTexture(dd.textures->at(1));
    player.setTextureRect(IntRect((frame) * 120, (int)state * 120, 120, 120));
    dd.window->draw(player);
}
