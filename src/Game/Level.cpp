#include "Level.h"

#include "../Utility/Logger.h"
#include "Coin.h"

Level::Level(Renderer* renderer)
    : m_renderer(renderer)
{
}

bool Level::Init(const std::string& filepath)
{
    m_maze.reset(new Maze(filepath, m_renderer));

    m_entityFactory.reset(new EntityFactory());
    Vec2 playerPos = Vec2(400.0f, 300.0f);
    Player* player = m_entityFactory->RegisterEntity<Player>(Vec2(400.0f, 300.0f), BoundingBox(playerPos, 16.0f, 16.0f));

    Vec2 coinPos = Vec2(600.0f, 200.0f);
    m_entityFactory->RegisterEntity<Coin>(Vec2(600.0f, 200.0f), BoundingBox(coinPos, 16.0f, 16.0f)); // TODO: Make this 32.0f (divide by two in AABB)
    m_playerController.reset(new PlayerController(player));

    return true;
}

void Level::OnUpdate(float timestep)
{
    m_maze->Draw();
    m_playerController->OnUpdate(timestep);

    Player* player = (Player*) m_entityFactory->GetEntities<ENTITY_PLAYER>().front();
    player->OnUpdate(timestep);

    for (Entity* e : m_entityFactory->GetEntities<ENTITY_COIN>())
    {
        e->OnUpdate(timestep);
        if (player->Collide(e))
        {
            player->OnEntityCollision(e);
        }
        m_renderer->Draw(e->GetSprite());
    }

    m_renderer->Draw(player->GetSprite());
}
