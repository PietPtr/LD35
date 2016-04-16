#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace sf;

int BACKGROUNDHEIGHT = 120; //px

struct Obstacle
{
    int lane;
    int index;
    float position;
};

enum Role
{
    START,
    END,
    MIDDLE
};

struct Background
{
    float position;
    int style; //style * 3 + role + startindex = texture index
    Role role; //basically the texture index
};

class World
{
    public:
        World();
        void update(double dt);
        void draw(DrawData dd);
    protected:
    private:
        std::vector<Obstacle> obstacles;
        int style = 0; //0: land, 1: air, 2: water
        double speed;
        std::vector<Background> backgrounds;
};

#endif // WORLD_H
