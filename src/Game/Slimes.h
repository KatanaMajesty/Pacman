#pragma once
#include "../Game/Entity.h"
#include "../Utility/Math.h"
#include "../Game/Maze.h"
#include "../Game/AnimationManager.h"
#include "vector"
#include "../Audio/AudioManager.h"


enum class Slimes
{
    FreezSlime,
    CoinSlime,
    FireSlime,
    SlowSlime,
    UNKNOWN
};



class Slime: public Entity
{
public:
    Slime(const Vec2& pos, const BoundingBox& boundingBox);
    /*inline uint16_t GetTargetDistance(const Vec2& PlayerPos, const Vec2& CurrentPos)
    {return sqrt(pow(PlayerPos.x - CurrentPos.x, 2) + pow(PlayerPos.y - CurrentPos.y, 2));}*/
    //virtual void move();
    //virtual void UpdatePath(const Vec2& PlayerPos)
    //{
    //  //  m_path = m_pf->invoke(m_pos, PlayerPos, Manhattan);
    //}
    virtual void OnUpdate(float timestep);
    virtual EntityType GetType()const { return ENTITY_ENEMY; }
    virtual Sprite* GetSprite() override { return &m_sprite; }
    virtual void OnEntityCollision(Entity* entity);
    virtual void SetPath(const std::vector<Vec2>& path) { m_path = path; }
    virtual bool IsArrived()const { return m_arrived; }

protected:
    std::vector<Vec2> m_path;
    float m_speed = 200.0f;
    Vec2 m_SlimePos;
    bool m_arrived = true;
    SpriteAnimation* m_animation;
    Sprite m_sprite;
}; 

//class FreezSlime : public ISlime
//{
//    FreezSlime(const Vec2& pos, const BoundingBox& boundingBox);
//    virtual void OnUpdate(float timestep) override;
//}; 

//class CoinSlime : public ISlime
//{
//    CoinSlime(const Vec2& pos, const BoundingBox& boundingBox) ::ISlime(pos, boundingBox, pf) {}
//    virtual void OnUpdate(float timestep) override;
//}; 
//
//class SlowSlime : public ISlime
//{
//    SlowSlime(const Vec2& pos, const BoundingBox& boundingBox) : : ISlime(pos, boundingBox, pf) {}
//    virtual void OnUpdate(float timestep) override;
//}; 

//class FireSlime : public ISlime
//{
//    FireSlime(const Vec2& pos, const BoundingBox& boundingBox);
//    void OnUpdate(float timestep, Vec2& PlayerPos);
//    virtual void move() override;
//};

