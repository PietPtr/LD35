#include <SFML/Graphics.hpp>
#include <iostream>
#include "Audio.h"
#include "include.h"
#include "Player.h"
#include "World.h"r

using namespace sf;

class Game
{
    public:
        Game(RenderWindow* window);
        void initialize();
        void update();
        void draw();
        bool isWindowOpen();

        void loadAudio(std::vector<std::string> fileNames);
        void loadTextures(std::vector<std::string> fileNames);

        int randint(int low, int high, int seed);
        int randint(int low, int high);
    protected:
    private:
        RenderWindow* window;

        Time dt;
        Time totalTime;
        Clock clock;
        int frame = 0;

        std::vector<std::string> audioFileNames { };
        std::vector<std::string> textureFileNames { "backgrounds.png", "player.png", "shift.png" };

        std::vector<Audio*> sfx;
        std::vector<Texture> textures;

        DrawData drawData;

        Player player;
        World world;
        Biome newBiome = LAND;
        Time lastBiomeChange = totalTime;
        double speed = 275; // px/s
};
