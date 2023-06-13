#include "pch.h"

bool BoundingBox::Collide(const BoundingBox& other) const
{
    bool collisionX = max.x >= other.min.x && min.x <= other.max.x;
    bool collisionY = max.y >= other.min.y && min.y <= other.max.y;
    return collisionX && collisionY;
}

Direction BoundingBox::GetCollisionDirection(const BoundingBox& other) const
{
    float bottomCollision = other.max.y - min.y;
    float topCollision = max.y - other.min.y;
    float leftCollision = max.x - other.min.x;
    float rightCollision = other.max.x - min.x;

    if (topCollision < bottomCollision && topCollision < leftCollision && topCollision < rightCollision)
        return Direction::DIRECTION_UP;
    if (bottomCollision < topCollision && bottomCollision < leftCollision && bottomCollision < rightCollision)
        return Direction::DIRECTION_DOWN;
    if (leftCollision < rightCollision && leftCollision < topCollision && leftCollision < bottomCollision)
        return Direction::DIRECTION_LEFT;
    if (rightCollision < leftCollision && rightCollision < topCollision && rightCollision < bottomCollision)
        return Direction::DIRECTION_RIGHT;

    return Direction::DIRECTION_UP;
}