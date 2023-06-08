#pragma once
#include <vector>

#include "../Core/Renderer.h"
#include "../Core/Texture.h"

constexpr uint8_t MAX_MAZE_WIDTH_IN_TILES = 32;
constexpr uint8_t MAX_MAZE_HEIGHT_IN_TILES = 32;


enum class CellType
{
    UNKNOWN = -1,
    WALL = 0,
    FLOOR = 1
};

class Cell
{
public:
    Cell();
    Cell(Sprite* sprite, CellType type);

    inline Sprite* GetSpriteToModify() { return m_sprite.get(); }

    inline const Sprite* GetSprite() const { return m_sprite.get(); }
    inline const CellType GetType() const { return m_type; }
private:
    std::unique_ptr<Sprite> m_sprite;
    CellType m_type;
};

class Maze
{
public:
    explicit Maze(const std::string& filepath, Renderer* renderer);

    void Draw();

    inline const std::vector<Cell>& GetGrid() const { return m_mazeGrid; }
    inline const uint16_t& GetWidth() const { return m_mazeWidth; }
    inline const uint16_t& GetHeight() const { return m_mazeHeight; }

private:
    void ParseMazeImage(const std::string& filepath);
private:
    Renderer* m_renderer;
    std::vector<Cell> m_mazeGrid;
    uint16_t m_mazeWidth;
    uint16_t m_mazeHeight;
};

