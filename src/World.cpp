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

    obstacles.push_back(getRandomObstacle(Time(), 600 - 3 * BACKGROUNDHEIGHT));
    obstacles.push_back(getRandomObstacle(Time(), 600 - 6 * BACKGROUNDHEIGHT));
}

Obstacle World::getRandomObstacle(Time totalTime, float position)
{
    std::cout << "function got position: " << position << "\n";
    int indices[3] = { 0, 2, 3 };

    Obstacle obstacle;
    obstacle.lane = randint(0, 2, totalTime);
    obstacle.position = position;
    obstacle.size = 1;
    if (obstacle.lane == 1)
    {
        obstacle.index = indices[randint(0, 2, totalTime)];
    }
    else if (obstacle.lane == 0)
    {
        if (randint(0, 1, totalTime))
            obstacle.index = 0;
        else
            obstacle.index = 2;
    }
    else if (obstacle.lane == 2)
    {
        obstacle.index = randint(2, 3, totalTime);
    }
    if (obstacle.index == 0)
        obstacle.size = 2;

    return obstacle;
}

void World::update(double dt, Biome newBiome, double speed, Time totalTime)
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
        Background newbg;
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

    deleteFirst = false;

    for (int i = 0; i < obstacles.size(); i++)
    {
        obstacles[i].position += dt * speed;
        if (obstacles[i].position > 840)
            deleteFirst = true;
    }

    if (deleteFirst)
    {
        obstacles.erase(obstacles.begin());
        Obstacle newObstacle = getRandomObstacle(totalTime, -240);
        obstacles.push_back(newObstacle);
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

    for (int i = 0; i < obstacles.size(); i++)
    {
        Sprite obstacle;
        obstacle.setPosition(Vector2f((obstacles[i].lane + 1) * 120, obstacles[i].position));
        obstacle.setTexture(dd.textures->at(3));
        obstacle.setTextureRect(IntRect(obstacles[i].index * 120, biome * 120, obstacles[i].size * 120, 120));
        dd.window->draw(obstacle);
    }
}

int World::randint(int low, int high, Time totalTime)
{
    int value = rand() % (high + 1 - low) + low;
    srand(totalTime.asMicroseconds() * value * rand());

    return value;
}
