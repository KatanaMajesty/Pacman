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


private:
  //pos
  //coincount
  //sprite
};

