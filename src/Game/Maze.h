#pragma once

#include <vector>
#include "../Core/Renderer.h"
#include "../Core/Texture.h"
#include "Tile.h"

class Maze
{
public:
    Maze(EntityFactory* entityFactory, Renderer* renderer);

    bool Init(const std::string& filepath);
    void Draw();
    inline auto& GetGrid() { return m_grid; }
    inline auto& GetGrid() const { return m_grid; }
    inline uint32_t GetWidth() const { return m_width; }
    inline uint32_t GetHeight() const { return m_height; }
    Vec2 GetPosition(uint32_t x, uint32_t y) const;
    float GetViewsize() const;

private:
    void ParseMazeImage(const std::string& filepath);

    EntityFactory* m_entityFactory;
    Renderer* m_renderer;
    std::vector<std::vector<Tile*>> m_grid;
    uint32_t m_width;
    uint32_t m_height;
    uint32_t m_textureWidth;
    uint32_t m_textureHeight;
};

