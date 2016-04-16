#ifndef PLAYER_H
#define PLAYER_H

enum State
{
    LAND, //change to animal
    BIRD,
    FISH
};

class Player
{
    public:
        Player();
        void update();
        void draw();
    protected:
    private:
        int lane; // 0: left, 1: center, 2: right
        int texture; // The index of the first texture
        State state = LAND;

};

#endif // PLAYER_H
