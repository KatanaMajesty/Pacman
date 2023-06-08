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

class Maze
{
public:
    explicit Maze(const char* mazeFilePath, const char cWall = '0', const char cFloor = '*');

    void Draw(Renderer* renderer);

    inline const std::vector<CellType>& GetGrid() const { return m_mazeGrid; }
    inline const uint16_t& GetWidth() const { return m_mazeWidth; }
    inline const uint16_t& GetHeight() const { return m_mazeHeight; }
    inline Texture* GetWallTexture() const { return m_mazeWallTexture; }
    inline Texture* GetFloorTexture() const { return m_mazeFloorTexture; }

    inline void SetWallTexture(Texture* wallTexture) { m_mazeWallTexture = wallTexture; }
    inline void SetFloorTexture(Texture* floorTexture) { m_mazeFloorTexture = floorTexture; }

private:
    void ParseMazeImage(const char* mazeFilePath, const char cWall = '0', const char cFloor = '*');
private:
    std::vector<CellType> m_mazeGrid;

    uint16_t m_mazeWidth;
    uint16_t m_mazeHeight;

    Texture* m_mazeWallTexture;
    Texture* m_mazeFloorTexture;
};

