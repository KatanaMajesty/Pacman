#pragma once
#include "../Game/Entity.h"
#include "../Utility/Math.h"
#include "../Game/Maze.h"

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
    ISlime(const Vec2& pos, const BoundingBox& boundingBox) : Entity(pos, boundingBox) {};
    inline uint16_t GetTargetDistance(const Vec2& PlayerPos, const Vec2& CurrentPos)
    {return sqrt(pow(PlayerPos.x - CurrentPos.x, 2) + pow(PlayerPos.y - CurrentPos.y, 2));}
    bool map_collision(const Direction& dir,Maze* maze);  

protected:
    float m_speed = 200.0f;
}; 

class FreezSlime : public ISlime
{
    virtual void OnUpdate(float timestep) override;
}; 

class CoinSlime : public ISlime
{
    virtual void OnUpdate(float timestep) override;
}; 

class SlowSlime : public ISlime
{
    virtual void OnUpdate(float timestep) override;
}; 

class FireSlime : public ISlime
{
    virtual void OnUpdate(float timestep) override;
};

