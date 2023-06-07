#pragma once
#include <SFML/Graphics.hpp>
#include "../Utility/Math.h"

class Player
{
public:
    Player();

    void SetPosition(float x, float y);
    const Vec2& GetPosition() const;
    void AddPosition(float offsetX, float offsetY);
    void SetRotation(float angle);

    float movementSpeed = 0.2f;

private:
    sf::CircleShape m_circle;
    sf::Texture m_texture1;
    sf::Texture m_texture2;
    bool m_useTexture1;
};

