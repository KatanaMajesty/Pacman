#pragma once

#include <vector>
#include "../Core/Renderer.h"
#include "../Core/Texture.h"
#include "Tile.h"

//enum class CellType
//{
//    UNKNOWN = -1,
//    WALL = 0,
//    FLOOR = 1
//};
//
//class Cell
//{
//public:
//    Cell();
//    Cell(Tile* tile, CellType type);
//
//    inline Tile* GetTile() { return m_tile; }
//    inline const CellType GetType() const { return m_type; }
//private:
//    Tile* m_tile;
//    CellType m_type;
//};

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

private:
    void ParseMazeImage(const std::string& filepath);

    EntityFactory* m_entityFactory;
    Renderer* m_renderer;
    std::vector<std::vector<Tile*>> m_grid;
    uint32_t m_width;
    uint32_t m_height;
};

