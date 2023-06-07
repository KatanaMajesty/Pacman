#include "PlayerController.h"
#include "Player.h"

PlayerController::PlayerController(Player& player, sf::RenderWindow& window)
    : m_player(player), m_window(window), m_windowSize(window.getSize())
{
}


void PlayerController::Update()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        OnMoveUp();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        OnMoveDown();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        OnMoveLeft();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        OnMoveRight();
    }
}

void OnMoveUp()
{

}

void OnMoveDown()
{

}

void OnMoveLeft()
{

}

void OnMoveRight()
{

}