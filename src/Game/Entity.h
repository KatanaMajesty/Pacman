#pragma once

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

	virtual void OnUpdate(float timestep) = 0;
	virtual void OnEntityCollision(Entity* entity) = 0;
	virtual EntityType GetType() const { return ENTITY_UNKNOWN; }
};