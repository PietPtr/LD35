#ifndef PLAYER_H
#define PLAYER_H
#include "World.h"

using namespace sf;

enum State
{
    BEAR, //change to animal
    BIRD,
    FISH
};

class Player
{
    public:
        Player();
        void update(double dt, Time totalTime);
        void draw(DrawData dd, Time totalTime, double speed);

        void pressedLeft(bool value) { wasLeftpressed = value; }
        void pressedRight(bool value) { wasRightpressed = value; }
        void setState(State value) { state = value; shiftShape = true; }
        State getState() { return state; }
    protected:
    private:
        Vector2f position { 240, 580 };
        bool wasLeftpressed = false;
        bool wasRightpressed = false;
        int lane = 1; // 0: left, 1: center, 2: right
        int texture; // The index of the first texture
        State state = BEAR;
        Time lanechangeTime;
        bool shiftShape = false;
};

#endif // PLAYER_H
