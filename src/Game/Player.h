#pragma once

#include "../Core/Sprite.h"
#include "../Utility/Math.h"
#include "Entity.h"

class Player : public Entity
{
public:
    Player();
    virtual ~Player() = default;

    virtual void OnUpdate(float timestep) override;
    virtual void OnEntityCollision(Entity* entity) override;
    virtual EntityType GetType() const { return ENTITY_PLAYER; }
    void OnCoinPickup();
    void OnWeaponPickup();
    void OnEnemyInteract();

private:
    bool m_hasWeapon = false;
    float m_timeSinceAnimationTick = 0.0f;
    Sprite m_sprite;
};