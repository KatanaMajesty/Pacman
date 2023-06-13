#include "pch.h"

bool BoundingBox::Collide(const BoundingBox& other) const
{
    if (max.x < other.min.x || min.x > other.max.x) {
        return false;  // No collision on the X-axis
    }

    if (max.y < other.min.y || min.y > other.max.y) {
        return false;  // No collision on the Y-axis
    }

    return true;  // Colliding on both X-axis and Y-axis
}