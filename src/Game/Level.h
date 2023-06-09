#pragma once

#include <memory>
#include <vector>
#include "../Core/Renderer.h"
#include "../Utility/EventBus.h"
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
    void OnWindowResize(const WindowResizedEvent& wre);
    void SetLevelScale(float x, float y) const;

private:
    Renderer* m_renderer;
    std::unique_ptr<Maze> m_maze;
    std::unique_ptr<EntityFactory> m_entityFactory = nullptr;
    std::unique_ptr<PlayerController> m_playerController;
};