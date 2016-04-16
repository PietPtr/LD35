#include "World.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

World::World()
{
    Background startbg;
    startbg.position = 600;
    startbg.role = START;
    startbg.biome = biome;
    backgrounds.push_back(startbg);

    for (int i = 1; i < 8; i++)
    {
        Background bg;
        bg.position = 600 - i * BACKGROUNDHEIGHT;
        bg.role = MIDDLE;
        bg.biome = biome;
        backgrounds.push_back(bg);
    }
}

void World::update(double dt, Biome newBiome, double speed)
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
        Background newbg; //maybe biome change here?
        newbg.position = backgrounds[backgrounds.size() - 1].position - BACKGROUNDHEIGHT;
        if (newBiome != biome)
        {
            if (backgrounds[backgrounds.size() - 1].role == END)
            {
                newbg.role = START;
                newbg.biome = (Biome)newBiome;
                biome = (Biome)newBiome;
            }
            else
            {
                newbg.role = END;
                newbg.biome =  backgrounds[backgrounds.size() - 1].biome;
            }
        }
        else
        {
            newbg.role = MIDDLE;
            newbg.biome =  backgrounds[backgrounds.size() - 1].biome;
        }
        backgrounds.push_back(newbg);
    }
}

void World::draw(DrawData dd)
{
    for (int i = 0; i < backgrounds.size(); i++)
    {
        Sprite background;
        background.setPosition(Vector2f(0, backgrounds[i].position));
        background.setTexture(dd.textures->at(0));
        background.setTextureRect(IntRect(0, backgrounds[i].biome * 360 + backgrounds[i].role * 120, 720, 120));
        dd.window->draw(background);
    }
}
