#include "Math.h"

bool BoundingBox::Collide(const BoundingBox& otherBounds) {

    return (max.x < otherBounds.min.x or min.x > otherBounds.max.x or
        max.y < otherBounds.min.y or min.y > otherBounds.max.y);
}