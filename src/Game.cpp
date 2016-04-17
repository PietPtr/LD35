#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace sf;

Game::Game(RenderWindow* _window)
{
    window = _window;
}

void Game::initialize()
{
    loadAudio(audioFileNames);
    loadTextures(textureFileNames);
    std::cout << "Found " << textures.size() << " textures in vector.\n";

    drawData.textures = &textures;
    drawData.window = window;

    sfx[0]->play();
    sfx[0]->setLoop(true);
}

void Game::update()
{
    Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
        if (event.type == Event::KeyPressed)
        {
            if (event.key.code == Keyboard::Escape)
            {
                window->close();
            }
            if (event.key.code == Keyboard::A)
                player.pressedLeft(true);
            if (event.key.code == Keyboard::D)
                player.pressedRight(true);
            if (event.key.code == Keyboard::Q || event.key.code == Keyboard::E)
            {
                int intstate = (int)player.getState();
                if (event.key.code == Keyboard::Q)
                    intstate--;
                else
                    intstate++;
                intstate = intstate < 0 ? 2 : intstate;
                intstate = intstate > 2 ? 0 : intstate;
                player.setState((State)intstate);

            }
        }
    }

    dt = clock.restart();
    totalTime += dt;

    if (gamestate == PLAYING)
    {
        if (randint(0, 1000) > 995 && totalTime.asSeconds() - lastBiomeChange.asSeconds() > 5)
        {
            newBiome = (Biome)randint(0, 2);
            lastBiomeChange = totalTime;
        }
        player.setBiome(world.getPlayerBiome());

        world.update(dt.asSeconds(), newBiome, speed, totalTime);
        player.update(dt.asSeconds(), totalTime, world.getObstacles());

        speed = 275 + totalTime.asSeconds() * 8;
        speed = speed > 750 ? 750 : speed;

        if (player.getLives() == 0)
        {
            gamestate = GAME_OVER;
            sfx[1]->play();
        }

        pxdistance += speed * dt.asSeconds();
    }
    else if (gamestate == GAME_OVER)
    {
        sfx[0]->stop();
        score = (int)(pxdistance / 120);
    }

    frame++;
}

void Game::draw()
{
    window->clear();

    world.draw(drawData);
    player.draw(drawData, totalTime, speed);

    if (gamestate == GAME_OVER)
    {
        Sprite gameover;
        gameover.setTexture(textures.at(5));
        gameover.setPosition(120, 240);
        window->draw(gameover);

        std::string scoreStr = std::to_string(score);
        for (int i = 0; i < scoreStr.length(); i++)
        {
            Sprite number;
            number.setPosition(Vector2f(i * 30, 0) + Vector2f(250, 305));
            number.setTexture(textures.at(6));
            number.setTextureRect(IntRect(((int)scoreStr[i] - 48) * 30, 0, 30, 30));
            window->draw(number);
            std::cout << ((int)scoreStr[i] - 48) * 30 << " " << scoreStr[i] << "\n";
        }
    }

    window->display();
}

bool Game::isWindowOpen()
{
    return window->isOpen();
}

void Game::loadAudio(std::vector<std::string> audioFileNames)
{
    for (int i = 0; i < audioFileNames.size(); i++)
    {
        sfx.push_back(new Audio());
        sfx.back()->init(audioFileNames[i]);
    }
}

void Game::loadTextures(std::vector<std::string> textureFileNames)
{
    for (int i = 0; i < textureFileNames.size(); i++)
    {
        Texture texture;
        if (!texture.loadFromFile("resources/textures/" + textureFileNames.at(i)))
            window->close();
        else
            std::cout << "loaded resources/textures/" << textureFileNames.at(i) << "\n";
        textures.push_back(texture);
    }
}

int Game::randint(int low, int high)
{
    int value = rand() % (high + 1 - low) + low;
    srand(totalTime.asMicroseconds() * value * rand());

    return value;
}
