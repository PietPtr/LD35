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
        }
    }

    dt = clock.restart();
    totalTime += dt;

    if (randint(0, 1000) > 995 && totalTime.asSeconds() - lastBiomeChange.asSeconds() > 5)
    {
        newBiome = (Biome)randint(0, 2);
        lastBiomeChange = totalTime;
        std::cout << "Changing biome!\n";
    }
    world.update(dt.asSeconds(), newBiome);
    player.update(dt.asSeconds());

    frame++;
}

void Game::draw()
{
    window->clear();

    world.draw(drawData);
    player.draw(drawData);

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
