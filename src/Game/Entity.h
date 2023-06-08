#pragma once

#include "../Utility/Math.h"

enum EntityType
{
	ENTITY_UNKNOWN,
	ENTITY_PLAYER,
	ENTITY_ENEMY,
	ENTITY_COIN,
	ENTITY_WEAPON,
};

class Entity
{
public:
	Entity(const Vec2& pos, const BoundingBox& boundingBox);
	virtual ~Entity() = default;

	virtual void OnUpdate(float timestep) = 0;
	virtual void OnEntityCollision(Entity* entity) = 0;
	virtual EntityType GetType() const { return ENTITY_UNKNOWN; }
	void AddPosition(const Vec2& offset) { m_pos += offset; }
	void SetPosition(const Vec2& pos) { m_pos = pos; }
	const Vec2& GetPosition() const { return m_pos; }
	const BoundingBox& GetAABB() const { return m_boundingBox; }
	bool Collide(const Entity& otherEntity) {};

protected:
	BoundingBox m_boundingBox;
	Vec2 m_pos;
};