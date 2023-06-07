#include "Controller.h"
#include "Player.h"

Controller::Controller(Player& player, sf::RenderWindow& window)
    : m_player(player), m_window(window), m_windowSize(window.getSize())
{
}

void Controller::processEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_window.close();
    }
}

void Controller::update()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        sf::Vector2f newPosition = m_player.getPosition();
        newPosition.y -= m_player.movementSpeed;

        if (newPosition.y - m_player.getRadius() >= 0)
        {
            m_player.setPosition(newPosition.x, newPosition.y);
            m_player.setRotation(270.f);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        sf::Vector2f newPosition = m_player.getPosition();
        newPosition.y += m_player.movementSpeed;

        if (newPosition.y <= m_windowSize.y - m_player.getRadius())
        {
            m_player.setPosition(newPosition.x, newPosition.y);
            m_player.setRotation(90.f);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        sf::Vector2f newPosition = m_player.getPosition();
        newPosition.x -= m_player.movementSpeed;

        if (newPosition.x - m_player.getRadius() >= 0)
        {
            m_player.setPosition(newPosition.x, newPosition.y);
            m_player.setRotation(180.f);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        sf::Vector2f newPosition = m_player.getPosition();
        newPosition.x += m_player.movementSpeed;

        if (newPosition.x <= m_windowSize.x - m_player.getRadius())
        {
            m_player.setPosition(newPosition.x, newPosition.y);
            m_player.setRotation(0.f);
        }
    }
}
