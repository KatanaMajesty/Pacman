#include <SFML/Graphics.hpp>
#include <cmath> // For the rotation calculation
#include "Player.h"
#include "Controller.h"

int main()
{
    int renderWidth = 1280, renderHeight = 720;

    sf::RenderWindow window(sf::VideoMode(renderWidth, renderHeight), "SFML Textured Player");

    Player player;
    player.setPosition(renderWidth / 2, renderHeight / 2);

    Controller controller(player, window);

    sf::Clock clock;
    sf::Time elapsed;

    while (window.isOpen())
    {
        controller.processEvents();
        controller.update();

        elapsed = clock.getElapsedTime();
        if (elapsed.asSeconds() >= 0.2)
        {
            player.swapTextures();
            clock.restart();
        }

        window.clear();

        player.draw(window);

        window.display();
    }

    return 0;
}
