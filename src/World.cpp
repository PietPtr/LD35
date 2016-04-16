#include "World.h"

World::World()
{
    Background startbg;
    startbg.position = 0;
    startbg.role = START;
    startbg.style = style;
    backgrounds.push_back(startbg);

    for (int i = 0; i < 8; i++)
    {
        Background bg;
        bg.position = i * BACKGROUNDHEIGHT;
        bg.role = MIDDLE;
        bg.style = style;
        backgrounds.push_back(bg);
    }
}

void World::update(double dt)
{

}

void World::draw(DrawData dd)
{

}
