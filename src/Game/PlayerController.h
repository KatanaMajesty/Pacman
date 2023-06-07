#pragma once
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Player.h"

class PlayerController
{
public:
    PlayerController(Player& player, sf::RenderWindow& window);

    void Update();
    void OnMoveUp();
    void OnMoveDown();
    void OnMoveLeft();
    void OnMoveRight();

private:
    Player& m_player;
    sf::RenderWindow& m_window;
    sf::Vector2u m_windowSize;
};