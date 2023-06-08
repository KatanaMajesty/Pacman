#pragma once

#include "../Core/Sprite.h"
#include "../Core/SpriteAnimation.h"
#include "../Utility/Math.h"
#include "Entity.h"

enum Direction
{
    DIRECTION_UP, // W
    DIRECTION_LEFT, // A
    DIRECTION_DOWN, // S
    DIRECTION_RIGHT, // D
};

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
    Vec2 m_position;
    bool m_hasWeapon = false;
    float m_timeSinceAnimationTick = 0.0f;
    Sprite m_sprites[4]; // Sprite for each direction
};