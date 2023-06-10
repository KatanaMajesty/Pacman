#include "Level.h"

#include <cstdlib>
#include "../Utility/Logger.h"
#include "../Audio/AudioManager.h"
#include "AnimationManager.h"
#include "Coin.h"
#include "Tile.h"

Level::Level(Renderer* renderer)
    : m_renderer(renderer)
{
}

bool Level::Init(const std::string& filepath)
{
    m_entityFactory.reset(new EntityFactory());
    Vec2 playerPos = Vec2(400.0f, 300.0f);
    Player* player = m_entityFactory->RegisterEntity<Player>(Vec2(400.0f, 300.0f), BoundingBox(playerPos, 16.0f, 16.0f));
    m_playerController.reset(new PlayerController(player));

    //Vec2 coinPos = Vec2(600.0f, 200.0f);
    //m_entityFactory->RegisterEntity<Coin>(coinPos, BoundingBox(coinPos, 16.0f, 16.0f)); // TODO: Make this 32.0f (divide by two in AABB)

    //coinPos = Vec2(200.0f, 200.0f);
    //m_entityFactory->RegisterEntity<Coin>(coinPos, BoundingBox(coinPos, 16.0f, 16.0f)); // TODO: Make this 32.0f (divide by two in AABB)
    //coinPos = Vec2(250.0f, 200.0f);
    //m_entityFactory->RegisterEntity<Coin>(coinPos, BoundingBox(coinPos, 16.0f, 16.0f)); // TODO: Make this 32.0f (divide by two in AABB)
    //coinPos = Vec2(225.0f, 200.0f);
    //m_entityFactory->RegisterEntity<Coin>(coinPos, BoundingBox(coinPos, 16.0f, 16.0f)); // TODO: Make this 32.0f (divide by two in AABB)
    //coinPos = Vec2(275.0f, 200.0f);
    //m_entityFactory->RegisterEntity<Coin>(coinPos, BoundingBox(coinPos, 16.0f, 16.0f)); // TODO: Make this 32.0f (divide by two in AABB)

    //coinPos = Vec2(400.0f, 200.0f);
    //m_entityFactory->RegisterEntity<Coin>(coinPos, BoundingBox(coinPos, 16.0f, 16.0f)); // TODO: Make this 32.0f (divide by two in AABB)

    m_maze.reset(new Maze(m_entityFactory.get(), m_renderer));
    m_maze->Init(filepath);
    uint32_t w = m_maze->GetWidth();
    uint32_t h = m_maze->GetHeight();
    for (uint32_t i = 0; i < 30; ++i)
    {
        uint32_t x = std::rand() % w;
        uint32_t y = std::rand() % h;
        Vec2 pos = m_maze->GetPosition(x, y);
        if (!m_maze->At(x, y)->IsCollider())
            m_entityFactory->RegisterEntity<Coin>(pos, BoundingBox(pos, 16.0f, 16.0f));
    }

    //EventBus::Get().subscribe(this, &Level::OnWindowResize);

    AudioManager::Get().PlaySound(AUDIO_AMBIENCE);
    return true;
}

void Level::OnUpdate(float timestep)
{
    AnimationManager::Get().OnUpdate(timestep);
    m_maze->Draw();

    Player* player = (Player*) m_entityFactory->GetEntities<ENTITY_PLAYER>().front();
    player->OnUpdate(timestep);

    // Player-Tile collisions and Tile drawing
    for (Entity* entity : m_entityFactory->GetEntities<ENTITY_TILE>())
    {
        Tile* tile = (Tile*)entity;
        // tile->OnUpdate(timestep);
        if (tile->IsCollider() && tile->Collide(player))
        {
            tile->OnEntityCollision(player);
            player->OnEntityCollision(tile);
            break;
        }
    }
    
    m_renderer->Draw(player->GetSprite());
    if (player->CanMove()) // Only update player controller if the player can move
        m_playerController->OnUpdate(timestep);

    // Player-Coin collisions and coin drawing
    for (Entity* e : m_entityFactory->GetEntities<ENTITY_COIN>())
    {
        e->OnUpdate(timestep);
        if (player->Collide(e))
        {
            player->OnEntityCollision(e);
            e->OnEntityCollision(player); // Actually coin does nothing here
            m_entityFactory->DestroyEntity(e);
            coinAmount++;
        }
        m_renderer->Draw(e->GetSprite());
    }
}
