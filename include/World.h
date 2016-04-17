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

enum Biome
{
    LAND,
    WATER,
    AIR
};

struct Obstacle
{
    int lane;
    int index;
    int size;
    float position;
};

enum Role
{
    END,
    MIDDLE,
    START,
};

struct Background
{
    float position;
    Biome biome;
    Role role;
};

class World
{
    public:
        World();
        void update(double dt, Biome newBiome, double speed, Time totalTime);
        void draw(DrawData dd);

        Biome getBiome() { return biome; }
        Biome getPlayerBiome() { return backgrounds.front().biome; }
        int randint(int low, int high, Time totalTime);
        Obstacle getRandomObstacle(Time totalTime, float position);
        std::vector<Obstacle> getObstacles() { return obstacles; }
    protected:
    private:
        std::vector<Obstacle> obstacles;
        Biome biome = LAND; // 0: land, 1: air, 2: water
        std::vector<Background> backgrounds;
};

#endif // WORLD_H
