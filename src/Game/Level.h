#pragma once

#include <memory>
#include <vector>
#include "../Core/Renderer.h"
#include "Entity.h"
#include "Maze.h"
#include "Player.h"
#include "PlayerController.h"

class Level
{
public:
    Level(Renderer* renderer);
    
    bool Init(const std::string& filepath);
    void OnUpdate(float timestep);
    inline void SetRenderer(Renderer* renderer) { m_renderer = renderer; }

private:
    Renderer* m_renderer;
    std::unique_ptr<Maze> m_maze;
    std::unique_ptr<EntityFactory> m_entityFactory = nullptr;
    Player* m_player;
    std::unique_ptr<PlayerController> m_playerController;
};