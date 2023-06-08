#include "Level.h"

#include "../Utility/Logger.h"

Level::Level(Renderer* renderer)
    : m_renderer(renderer)
{
}

bool Level::Init(const std::string& filepath)
{
    m_maze.reset(new Maze(filepath, m_renderer));
    m_player.reset(new Player(Vec2(400.0f, 300.0f), BoundingBox()));
    m_playerController.reset(new PlayerController(m_player.get()));
    return true;
}

void Level::OnUpdate(float timestep)
{
    m_maze->Draw();

    m_playerController->OnUpdate(timestep);
    m_player->OnUpdate(timestep);

    m_renderer->Draw(m_player->GetSprite());
}
