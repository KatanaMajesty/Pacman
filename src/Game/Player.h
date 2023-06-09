#pragma once

#include "../Core/Sprite.h"
#include "../Core/SpriteAnimation.h"
#include "../Utility/Math.h"
#include "Entity.h"



class Player : public Entity
{
public:
    Player(const Vec2& pos, const BoundingBox& boundingBox);
    virtual ~Player() = default;

    // OnUpdate will update the position of sprites, AABB and CanMove state
    // Should be called before updating all the Tiles
    virtual void OnUpdate(float timestep) override;
    
    virtual void OnEntityCollision(Entity* entity) override;
    virtual EntityType GetType() const { return ENTITY_PLAYER; }
    virtual Sprite* GetSprite() override { return m_activeSprite; }
    void OnCoinPickup();
    void OnWeaponPickup();
    void OnEnemyInteract();
    void OnTileCollision();
    void SetDirection(Direction direction);

private:
    Vec2 m_playerPos;
    bool m_hasWeapon = false;
    float m_lastTimestep = 0.0f;
    float m_timeSinceAnimationTick = 0.0f;
    uint32_t m_collectedCoins = 0;
    Sprite* m_activeSprite = nullptr;
    Sprite m_sprites[4]; // Sprite for each direction
    Direction m_direction;
};