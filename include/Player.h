#ifndef PLAYER_H
#define PLAYER_H
#include "World.h"

using namespace sf;

enum State
{
    SQUIRREL, //change to animal
    FISH,
    BIRD
};

class Player
{
    public:
        Player();
        void update(double dt, Time totalTime, std::vector<Obstacle> obstacles);
        void draw(DrawData dd, Time totalTime, double speede);

        void pressedLeft(bool value) { wasLeftpressed = value; }
        void pressedRight(bool value) { wasRightpressed = value; }
        void setState(State value) { state = value; shiftShape = true; }
        State getState() { return state; }
        int getLives() { return lives; }
        void setBiome(Biome value) { biome = value; }
    protected:
    private:
        Vector2f position { 240, 580 };
        float rotation = 0;
        bool wasLeftpressed = false;
        bool wasRightpressed = false;
        int lane = 1; // 0: left, 1: center, 2: right
        int texture; // The index of the first texture
        State state = SQUIRREL;
        Time lanechangeTime;
        bool shiftShape = false;
        float timeHit = -1;
        int lives = 3;
        Biome biome = LAND;
        float wrongForm = -1;
};

#endif // PLAYER_H
