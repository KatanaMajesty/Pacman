#pragma once
#include <vector>

#include "../Core/Renderer.h"
#include "Maze.h"

class Level
{
public:
    Level(const char* mazeFilePath, const char cWall = '*', const char cFloor = '0');
    
    void Draw();

    inline void SetRenderer(Renderer* renderer) { m_renderer = renderer; }
    inline void SetMazeWallTexture(Texture* mazeWallTexture) { m_maze.SetWallTexture(mazeWallTexture); }
    inline void SetMazeFloorTexture(Texture* mazeFloorTexture) { m_maze.SetFloorTexture(mazeFloorTexture); }

private:
    Renderer* m_renderer;
    Maze m_maze;
};