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
	Entity() = default;
	virtual ~Entity() = default;

	void Init(const Vec2& pos, BoundingBox bounds);
	virtual void OnUpdate(float timestep) = 0;
	virtual void OnEntityCollision(Entity* entity) = 0;
	virtual EntityType GetType() const { return ENTITY_UNKNOWN; }

protected:
	BoundingBox m_bounds;
	Vec2 m_pos;
};