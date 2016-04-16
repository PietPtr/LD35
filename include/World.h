#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include <SFML/Graphics.hpp>
//#include "include.h"

using namespace sf;

const int BACKGROUNDHEIGHT = 120; //px

struct DrawData
{
    sf::RenderWindow* window;
    std::vector<sf::Texture>* textures;
};

struct Obstacle
{
    int lane;
    int index;
    float position;
};

enum Role
{
    END,
    MIDDLE,
    START,
};

enum Biome
{
    LAND,
    WATER,
    AIR
};

struct Background
{
    float position;
    Biome biome;
    Role role; //basically the texture index
};


class World
{
    public:
        World();
        void update(double dt, Biome newBiome);
        void draw(DrawData dd);

        Biome getBiome() { return biome; }
    protected:
    private:
        std::vector<Obstacle> obstacles;
        Biome biome = LAND; // 0: land, 1: air, 2: water
        double speed = 275; // px/s
        std::vector<Background> backgrounds;
};

#endif // WORLD_H
