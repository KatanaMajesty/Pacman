#include "Entity.h"

Entity::Entity(const Vec2& pos, const BoundingBox& boundingBox)
    : m_boundingBox(boundingBox)
    , m_pos(pos)
{
}

bool Entity::Collide(const Entity& otherEntity) 
{
    return m_boundingBox.Collide(otherEntity.m_boundingBox);
}

EntityFactory::~EntityFactory()
{
	// Clean up dynamically allocated entities
	for (auto& pair : m_entities)
	{
		for (Entity* e : pair.second)
			delete e;
	}
}
