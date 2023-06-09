#include "Level.h"

#include "../Utility/Logger.h"
#include "../Audio/AudioManager.h"
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

    Vec2 coinPos = Vec2(600.0f, 200.0f);
    m_entityFactory->RegisterEntity<Coin>(coinPos, BoundingBox(coinPos, 16.0f, 16.0f)); // TODO: Make this 32.0f (divide by two in AABB)

    coinPos = Vec2(200.0f, 200.0f);
    m_entityFactory->RegisterEntity<Coin>(coinPos, BoundingBox(coinPos, 16.0f, 16.0f)); // TODO: Make this 32.0f (divide by two in AABB)
    coinPos = Vec2(250.0f, 200.0f);
    m_entityFactory->RegisterEntity<Coin>(coinPos, BoundingBox(coinPos, 16.0f, 16.0f)); // TODO: Make this 32.0f (divide by two in AABB)
    coinPos = Vec2(225.0f, 200.0f);
    m_entityFactory->RegisterEntity<Coin>(coinPos, BoundingBox(coinPos, 16.0f, 16.0f)); // TODO: Make this 32.0f (divide by two in AABB)
    coinPos = Vec2(275.0f, 200.0f);
    m_entityFactory->RegisterEntity<Coin>(coinPos, BoundingBox(coinPos, 16.0f, 16.0f)); // TODO: Make this 32.0f (divide by two in AABB)

    coinPos = Vec2(400.0f, 200.0f);
    m_entityFactory->RegisterEntity<Coin>(coinPos, BoundingBox(coinPos, 16.0f, 16.0f)); // TODO: Make this 32.0f (divide by two in AABB)

    m_maze.reset(new Maze(m_entityFactory.get(), m_renderer));
    m_maze->Init(filepath);

    EventBus::Get().subscribe(this, &Level::OnWindowResize);

    AudioManager::Get().PlaySound(AUDIO_AMBIENCE);
    return true;
}

void Level::OnUpdate(float timestep)
{
    //m_maze->Draw();

    Player* player = (Player*) m_entityFactory->GetEntities<ENTITY_PLAYER>().front();
    player->OnUpdate(timestep);

    //// Here we will update the tiles and other stuff
    //player->CanMove() = false; // CanMove will be set to false if the player collides with a tile

    // Player-Tile collisions and Tile drawing
    for (Entity* entity : m_entityFactory->GetEntities<ENTITY_TILE>())
    {
        Tile* tile = (Tile*)entity;
        tile->OnUpdate(timestep);
        if (tile->IsCollider() && tile->Collide(player))
        {
            player->OnEntityCollision(tile);
            tile->OnEntityCollision(player);
        }
        m_renderer->Draw(tile->GetSprite());
    }

    for (Entity* entity : m_entityFactory->GetEntities<ENTITY_TILE>())
    {
        Tile* tile = (Tile*)entity;
        if (tile->IsCollider())
            m_renderer->Draw(tile->GetAABB().min, tile->GetAABB().max);
    }
    
    m_renderer->Draw(player->GetSprite());
    m_renderer->Draw(player->GetAABB().min, player->GetAABB().max);
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
        }
        m_renderer->Draw(e->GetSprite());
        m_renderer->Draw(e->GetAABB().min, e->GetAABB().max);
    }

}

void Level::OnWindowResize(const WindowResizedEvent& wre)
{
    float desiredTileWidth = static_cast<float>(wre.width) / static_cast<float>(m_maze.get()->GetWidth());
    float desiredTileHeight = static_cast<float>(wre.height) / static_cast<float>(m_maze.get()->GetHeight());

    //SetLevelScale(desiredTileWidth, desiredTileHeight);
}

//void Level::SetLevelScale(float x, float y) const
//{
//    for (auto& cell : m_maze.get()->GetGrid())
//    {
//        cell.GetSprite()->SetScale(x / cell.GetSprite()->GetTexture()->GetWidth(),
//            y / cell.GetSprite()->GetTexture()->GetHeight());
//    }
//}
