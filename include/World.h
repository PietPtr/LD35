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

struct Background
{
    float position;
    int style;
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
        double speed = 275; //px/s
        std::vector<Background> backgrounds;
};

#endif // WORLD_H
