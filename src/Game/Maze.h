#pragma once

#include <vector>
#include "../Core/Renderer.h"
#include "../Core/Texture.h"
#include "Tile.h"
#include "Pathfinder.h"

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
    Vec2 GetCenterPosition() const;
    const Tile* At(uint32_t x, uint32_t y) const { return m_grid.at(x).at(y); }
    float GetViewsize() const;
    inline Tile* GetTile(uint32_t x, uint32_t y);

    // TODO: remove
    const auto& GetPositions() const { return m_positions; }

private:
    void ParseMazeImage(const std::string& filepath);

    EntityFactory* m_entityFactory;
    Renderer* m_renderer;
    std::vector<std::vector<Tile*>> m_grid;
    std::vector<Pathfinder::PositionType> m_path;
    std::vector<Vec2> m_positions;
    uint32_t m_width;
    uint32_t m_height;
    uint32_t m_textureWidth;
    uint32_t m_textureHeight;
};

