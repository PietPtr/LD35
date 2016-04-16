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

void Player::draw(DrawData dd)
{
    RectangleShape player;
    player.setPosition(position);
    switch((int)state)
    {
    case(0):
        player.setFillColor(Color(97, 65, 13));
        break;
    case(1):
        player.setFillColor(Color(250, 225, 185));
        break;
    case(2):
        player.setFillColor(Color(0, 36, 94));
        break;
    default:
        player.setFillColor(Color(255, 0, 255));
    }
    player.setSize(Vector2f(120, 120));
    dd.window->draw(player);
}
