#pragma once

#include <vector>
#include "Entity.h"
#include "../Utility/Math.h"
#include "../Utility/Clock.h"
#include "../Audio/AudioManager.h"
#include "../Core/SpriteAnimation.h"

class Slime: public Entity
{
public:
    Slime(const Vec2& pos, const BoundingBox& boundingBox);

    virtual void OnUpdate(float timestep);
    virtual EntityType GetType()const { return ENTITY_ENEMY; }
    virtual Sprite* GetSprite() override { return &m_sprite; }
    virtual void OnEntityCollision(Entity* entity);
    void SetPath(const std::vector<Vec2>& path) { m_path = path; }
    bool IsArrived()const { return m_arrived; }
    void SetAttackInterval(float interval) { m_attackInterval = interval; }

protected:
    std::vector<Vec2> m_path;
    float m_speed = 200.0f;
    Vec2 m_SlimePos;
    bool m_arrived = true;
    SpriteAnimation* m_animation;
    Sprite m_sprite;
    float m_attackInterval = 4.0f;
    float m_timeSinceLastAttack = 0.0f;
}; 