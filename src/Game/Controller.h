#pragma once
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Player.h"

class Controller
{
public:
    Controller(Player& player, sf::RenderWindow& window);

    void processEvents();
    void update();

private:
    Player& m_player;
    sf::RenderWindow& m_window;
    sf::Vector2u m_windowSize;
};