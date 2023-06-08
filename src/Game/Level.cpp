#include "Level.h"

#include "../Utility/Logger.h"

Level::Level(Renderer* renderer)
    : m_renderer(renderer)
{
}

bool Level::Init(const std::string& filepath)
{
    m_maze.reset(new Maze(filepath, m_renderer));

    m_entityFactory.reset(new EntityFactory());
    Player* player = m_entityFactory->RegisterEntity<Player>(Vec2(400.0f, 300.0f), BoundingBox());
    m_playerController.reset(new PlayerController(player));

    return true;
}

void Level::OnUpdate(float timestep)
{
    m_maze->Draw();
    m_playerController->OnUpdate(timestep);

    Player* player = (Player*) m_entityFactory->GetEntities<ENTITY_PLAYER>().front();
    player->OnUpdate(timestep);

    m_renderer->Draw(player->GetSprite());
}
