#pragma once

#include "Entity.h"

class Tile : public Entity
{
public:
    Tile(const Vec2& pos, const BoundingBox& boundingBox);
    virtual ~Tile() = default;

    virtual void OnUpdate(float timestep) override {}
    virtual void OnEntityCollision(Entity* entity) override;
    virtual EntityType GetType() const { return ENTITY_TILE; }
    virtual Sprite* GetSprite() override { return &m_sprite; }

private:
    Sprite m_sprite;
};