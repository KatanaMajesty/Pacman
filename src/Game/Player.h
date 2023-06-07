#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
    Player();

    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    void move(float offsetX, float offsetY);
    void draw(sf::RenderWindow& window);
    void swapTextures();
    float getRadius() const;
    void setRotation(float angle); // New function added

    float movementSpeed = 0.2f;

private:
    sf::CircleShape m_circle;
    sf::Texture m_texture1;
    sf::Texture m_texture2;
    bool m_useTexture1;
};

