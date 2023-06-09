#pragma once
#include "../Pacman/src/Game/Entity.h"
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
    
}; 

class FreezSlime : public ISlime
{

}; 

class CoinSlime : public ISlime
{

}; 

class SlowRobot : public ISlime
{

}; 

class FireSlime : public ISlime
{

};

