#include "Level.h"

#include "../Utility/Logger.h"

Level::Level(const char* mazeFilePath, const char cWall, const char cFloor)
    : m_maze(mazeFilePath, cWall, cFloor)
{
    
}

void Level::Draw()
{
    m_maze.Draw(m_renderer);
}
