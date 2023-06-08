#include "Entity.h"

Entity::Entity(const Vec2& pos, const BoundingBox& boundingBox)
    : m_boundingBox(boundingBox)
    , m_pos(pos)
{
}
