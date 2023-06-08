#include "Math.h"

bool BoundingBox::Collide(const BoundingBox& otherBounds) {

    if (m_max.x < otherBounds.m_min.x or m_min.x > otherBounds.m_max.x) { return false; };
    if (m_max.y < otherBounds.m_min.y or m_min.y > otherBounds.m_max.y) { return false; };
        
    return true;
}