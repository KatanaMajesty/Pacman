#include "Entity.h"

void Entity::Init(const Vec2& pos, BoundingBox bounds) {
    m_bounds = bounds;
    m_pos = pos;
}