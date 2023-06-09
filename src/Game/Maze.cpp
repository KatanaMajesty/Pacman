#include "Maze.h"

#include <fstream>
#include <sstream>
#include <string>
#include "TextureAtlas.h"
#include "../Utility/Logger.h"

Maze::Maze(const std::string& filepath, Renderer* renderer)
    : m_renderer(renderer), m_mazeWidth(0), m_mazeHeight(0)
{
    ParseMazeImage(filepath);
}

void Maze::Draw()
{
    float desiredTileWidth = static_cast<float>(m_renderer->GetWindowWidth()) / static_cast<float>(m_mazeWidth);
    float desiredTileHeight = static_cast<float>(m_renderer->GetWindowHeight()) / static_cast<float>(m_mazeHeight);

    for (uint32_t i = 0; i < m_mazeWidth; i++)
    {
        for (uint32_t j = 0; j < m_mazeHeight; j++)
        {
            Sprite* cellSprite = m_mazeGrid[static_cast<size_t>(i * m_mazeWidth + j)].GetSprite();

            cellSprite->SetPosition(Vec2(j * desiredTileWidth, i * desiredTileHeight));
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

    m_mazeWidth = static_cast<uint16_t>(line.size());
    m_mazeHeight = static_cast<uint16_t>(mazeString.size() / m_mazeWidth);

    TextureAtlas& atlas = TextureAtlas::Get();
    for (size_t i = 0; i < mazeString.size(); ++i)
    {
        if (mazeString[i] == '0')
        {
            m_mazeGrid.emplace_back(new Sprite(), CellType::WALL);
            m_mazeGrid[i].GetSprite()->SetTexture(atlas.GetTexture(TextureType::TEXTURE_DUNGEON_WALL1));
        }
        else if (mazeString[i] == '*')
        {
            m_mazeGrid.emplace_back(new Sprite(), CellType::FLOOR);
            m_mazeGrid[i].GetSprite()->SetTexture(atlas.GetTexture(TextureType::TEXTURE_DUNGEON_TILE));
        }
    }

    mazeImageFile.close();
}

Cell::Cell()
    : m_sprite(nullptr), m_type(CellType::UNKNOWN)
{
}

Cell::Cell(Sprite* sprite, CellType type)
    : m_sprite(sprite), m_type(type)
{
}
