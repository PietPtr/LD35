#include "World.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

World::World()
{
    Background startbg;
    startbg.position = 600;
    startbg.role = START;
    startbg.style = style;
    backgrounds.push_back(startbg);

    for (int i = 1; i < 8; i++)
    {
        Background bg;
        bg.position = 600 - i * BACKGROUNDHEIGHT;
        bg.role = MIDDLE;
        bg.style = style;
        backgrounds.push_back(bg);
    }
}

void World::update(double dt)
{
    bool deleteFirst = false;

    for (int i = 0; i < backgrounds.size(); i++)
    {
        backgrounds[i].position += dt * speed;
        if (backgrounds[i].position > 840)
            deleteFirst = true;
    }

    if (deleteFirst)
    {
        backgrounds.erase(backgrounds.begin());
        Background newbg; //maybe style change here?
        newbg.position = backgrounds[backgrounds.size() - 1].position - BACKGROUNDHEIGHT;
        newbg.role = MIDDLE;
        newbg.style =  backgrounds[backgrounds.size() - 1].style;
        backgrounds.push_back(newbg);
    }

    std::cout << backgrounds.size() << "\n";
}

void World::draw(DrawData dd)
{
    for (int i = 0; i < backgrounds.size(); i++)
    {
        Sprite background;
        background.setPosition(Vector2f(0, backgrounds[i].position));
        background.setTexture(dd.textures->at(0));
        background.setTextureRect(IntRect(0, backgrounds[i].style * 360 + backgrounds[i].role * 120, 720, 120));
        dd.window->draw(background);
    }
}
