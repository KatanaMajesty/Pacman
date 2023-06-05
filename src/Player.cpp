#include "Player.h"


Player::Player()
{
    m_circle.setRadius(20.f);
    m_circle.setFillColor(sf::Color::Yellow);
    m_circle.setOrigin(20.f, 20.f);
    m_texture1.loadFromFile("./pacman1.png");
    m_texture2.loadFromFile("./pacman2.png");
    m_useTexture1 = true;
}

void Player::setPosition(float x, float y)
{
    m_circle.setPosition(x, y);
}

sf::Vector2f Player::getPosition() const
{
    return m_circle.getPosition();
}

void Player::move(float offsetX, float offsetY)
{
    m_circle.move(offsetX, offsetY);
}

void Player::draw(sf::RenderWindow& window)
{
    if (m_useTexture1)
        m_circle.setTexture(&m_texture1);
    else
        m_circle.setTexture(&m_texture2);

    window.draw(m_circle);
}

void Player::swapTextures()
{
    m_useTexture1 = !m_useTexture1;
}

float Player::getRadius() const
{
    return m_circle.getRadius();
}

void Player::setRotation(float angle)
{
    m_circle.setRotation(angle);
}
