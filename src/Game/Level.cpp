#include "Level.h"

#include "../Utility/Logger.h"
#include "Coin.h"
#include "Tile.h"

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
    m_playerController.reset(new PlayerController(player));

    Vec2 coinPos = Vec2(600.0f, 200.0f);
    m_entityFactory->RegisterEntity<Coin>(coinPos, BoundingBox(coinPos, 16.0f, 16.0f)); // TODO: Make this 32.0f (divide by two in AABB)

    coinPos = Vec2(200.0f, 200.0f);
    m_entityFactory->RegisterEntity<Coin>(coinPos, BoundingBox(coinPos, 16.0f, 16.0f)); // TODO: Make this 32.0f (divide by two in AABB)

    coinPos = Vec2(400.0f, 200.0f);
    m_entityFactory->RegisterEntity<Coin>(coinPos, BoundingBox(coinPos, 16.0f, 16.0f)); // TODO: Make this 32.0f (divide by two in AABB)

    Vec2 tilepos = Vec2(400.0f, 300.0f);
    m_entityFactory->RegisterEntity<Tile>(tilepos, BoundingBox(tilepos, 32.0f, 32.0f), true);

    EventBus::Get().subscribe(this, &Level::OnWindowResize);

    return true;
}

void Level::OnUpdate(float timestep)
{
    //m_maze->Draw();

    Player* player = (Player*) m_entityFactory->GetEntities<ENTITY_PLAYER>().front();
    player->OnUpdate(timestep);
    m_renderer->Draw(player->GetSprite());

    //// Here we will update the tiles and other stuff
    //player->CanMove() = false; // CanMove will be set to false if the player collides with a tile

    // Player-Tile collisions and Tile drawing
    for (Entity* tile : m_entityFactory->GetEntities<ENTITY_TILE>())
    {
        tile->OnUpdate(timestep);
        if (tile->Collide(player))
        {
            player->OnEntityCollision(tile);
            tile->OnEntityCollision(player);
        }
        m_renderer->Draw(tile->GetSprite());
    }


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
    }

}

void Level::OnWindowResize(const WindowResizedEvent& wre)
{
    SetLevelScale(0.0f, 0.0f);
}

void Level::SetLevelScale(float x, float y) const
{
    
}
