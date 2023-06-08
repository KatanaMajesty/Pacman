#include "Level.h"

#include "../Utility/Logger.h"

Level::Level(Renderer* renderer)
    : m_renderer(renderer)
{
}

bool Level::Init(const std::string& filepath)
{
    m_maze.reset(new Maze(filepath));

    m_entityFactory.reset(new EntityFactory());
    m_player = m_entityFactory->RegisterEntity<Player>(Vec2(400.0f, 300.0f), BoundingBox());
    m_playerController.reset(new PlayerController(m_player));

    return true;
}

void Level::OnUpdate(float timestep)
{
    m_maze->Draw(m_renderer);

    m_playerController->OnUpdate(timestep);
    m_entityFactory->GetEntities<EntityType::ENTITY_PLAYER>().front()->OnUpdate(timestep);

    m_renderer->Draw(m_player->GetSprite());
}
