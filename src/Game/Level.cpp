#include "Level.h"

#include "../Utility/Logger.h"

Level::Level(const char* mazeFilePath, const char cWall, const char cFloor)
    : m_maze(mazeFilePath, cWall, cFloor)
    , m_player(Vec2(400.0f, 300.0f), BoundingBox())
    , m_playerController(&m_player)
{
}

void Level::OnUpdate(float timestep)
{
    m_maze.Draw(m_renderer);

    m_playerController.OnUpdate(timestep);
    m_player.OnUpdate(timestep);

    m_renderer->Draw(m_player.GetSprite());
}
