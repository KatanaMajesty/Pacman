#pragma once
#include "../Game/Entity.h"
#include "../Utility/Math.h"
#include "../Game/Maze.h"
#include "../Game/PathFinding.h"

enum class BehaviorSlime 
{
    Chase,
    Scatter,
    Frightened,
    UNKNOWN
};

enum class Slimes
{
    FreezSlime,
    CoinSlime,
    FireSlime,
    SlowSlime,
    UNKNOWN
};



class ISlime: public Entity
{
public:
    ISlime(const Vec2& pos, const BoundingBox& boundingBox, std::shared_ptr<Pathfinder>& pf) : Entity(pos, boundingBox),m_pf(pf) {};
    /*inline uint16_t GetTargetDistance(const Vec2& PlayerPos, const Vec2& CurrentPos)
    {return sqrt(pow(PlayerPos.x - CurrentPos.x, 2) + pow(PlayerPos.y - CurrentPos.y, 2));}*/
    virtual void move() = 0;
    virtual void UpdatePath(const Vec2& PlayerPos)
    {
        m_path = m_pf->invoke(m_pos, PlayerPos, Manhattan);
    }


protected:
    std::vector<Vec2> m_path;
    float m_speed = 200.0f;
    Sprite m_sprites[2]; 
    Vec2 m_SlimePos;
    bool m_should_update_path = true;
    std::shared_ptr<Pathfinder> m_pf;
}; 

class FreezSlime : public ISlime
{
    FreezSlime(const Vec2& pos, const BoundingBox& boundingBox, std::shared_ptr<Pathfinder>& pf) : ISlime(pos, boundingBox, pf) {}
    virtual void OnUpdate(float timestep) override;
}; 

class CoinSlime : public ISlime
{
    CoinSlime(const Vec2& pos, const BoundingBox& boundingBox) : ISlime(pos, boundingBox) {}
    virtual void OnUpdate(float timestep) override;
}; 

class SlowSlime : public ISlime
{
    SlowSlime(const Vec2& pos, const BoundingBox& boundingBox) : ISlime(pos, boundingBox) {}
    virtual void OnUpdate(float timestep) override;
}; 

class FireSlime : public ISlime
{
    FireSlime(const Vec2& pos, const BoundingBox& boundingBox, std::shared_ptr<Pathfinder>& pf) : ISlime(pos, boundingBox,pf){}
    void OnUpdate(float timestep, Vec2& PlayerPos);
    virtual void move() override;
};

