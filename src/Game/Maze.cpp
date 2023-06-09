#include "Maze.h"

#include <fstream>
#include <sstream>
#include <string>
#include "TextureAtlas.h"
#include "../Utility/Logger.h"

Maze::Maze(EntityFactory* entityFactory, Renderer* renderer)
    : m_entityFactory(entityFactory)
    , m_renderer(renderer)
    , m_width(0)
    , m_height(0)
{
}

bool Maze::Init(const std::string& filepath)
{
    m_grid.clear();
    ParseMazeImage(filepath);
    return true;
}

void Maze::Draw()
{
    uint32_t textureWidth = TextureAtlas::Get().GetTextureWidth();
    uint32_t textureHeight = TextureAtlas::Get().GetTextureHeight();
    for (uint32_t x = 0; x < m_width; ++x)
    {
        for (uint32_t y = 0; y < m_height; ++y)
        {
            //size_t index = x + m_width * y;
            Sprite* cellSprite = m_grid[x][y]->GetSprite();

            cellSprite->SetPosition(Vec2(x * textureWidth, y * textureHeight));
            m_renderer->Draw(cellSprite);
        }
    }
}

void Maze::ParseMazeImage(const std::string& filepath)
{
    std::ifstream mazeImageFile(filepath);

    if (!mazeImageFile.is_open())
    {
        LOG("Failed to open maze image file");
        return;
    }

    std::ostringstream oss;
    std::string line;

    while (std::getline(mazeImageFile, line))
        oss << line;

    std::string mazeString = oss.str();

    m_width = static_cast<uint32_t>(line.size());
    m_height = static_cast<uint32_t>(mazeString.size()) / m_width;

    // Resize the grid
    m_grid.resize(m_width);
    for (auto& col : m_grid)
        col.resize(m_height);

    uint32_t textureWidth = TextureAtlas::Get().GetTextureWidth();
    uint32_t textureHeight = TextureAtlas::Get().GetTextureHeight();
    for (uint32_t x = 0; x < m_width; ++x)
    {
        for (uint32_t y = 0; y < m_height; ++y)
        {
            Vec2 pos = Vec2(x * textureWidth, y * textureHeight);
            size_t index = x + m_width * y;
            bool isWall = mazeString[index] == '0';
            TextureType type = isWall ? TEXTURE_DUNGEON_WALL1 : TEXTURE_DUNGEON_TILE;
            Tile* tile = m_entityFactory->RegisterEntity<Tile>(pos, BoundingBox(pos, textureWidth, textureHeight), type, isWall);
            m_grid[x][y] = tile;
        }
    }

    mazeImageFile.close();
}

//Cell::Cell()
//    : m_sprite(nullptr), m_type(CellType::UNKNOWN)
//{
//}
//
//Cell::Cell(Sprite* sprite, CellType type)
//    : m_sprite(sprite), m_type(type)
//{
//}
