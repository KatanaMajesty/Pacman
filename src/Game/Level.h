#pragma once
#include <vector>

#include "../Core/Renderer.h"
#include "Maze.h"
#include "Player.h"
#include "PlayerController.h"

class Level
{
public:
    Level(const char* mazeFilePath, const char cWall = '*', const char cFloor = '0');
    
    void OnUpdate(float timestep);
    inline void SetRenderer(Renderer* renderer) { m_renderer = renderer; }

private:
    Renderer* m_renderer;
    Maze m_maze;
    Player m_player;
    PlayerController m_playerController;
};