#include "Maze.h"

#include <fstream>
#include <sstream>
#include <string>
#include "TextureAtlas.h"
#include "../Utility/Logger.h"

Maze::Maze(const char* mazeFilePath, const char cWall, const char cFloor)
    :m_mazeWidth(0), m_mazeHeight(0)
{
    ParseMazeImage(mazeFilePath, cWall, cFloor);
}

void Maze::Draw(Renderer* renderer)
{
    TextureAtlas& atlas = TextureAtlas::Get();
    for (uint16_t i = 0; i < m_mazeWidth; i++)
    {
        for (uint16_t j = 0; j < m_mazeHeight; j++)
        {
            const CellType& cell = m_mazeGrid[static_cast<size_t>(i * m_mazeWidth + j)];
            Sprite currMazeObj;

            switch (cell)
            {
            case CellType::WALL:
                currMazeObj.SetTexture(atlas.GetTexture(TextureType::TEXTURE_DUNGEON_WALL1));
                break;
            case CellType::FLOOR:
                currMazeObj.SetTexture(atlas.GetTexture(TextureType::TEXTURE_DUNGEON_TILE));
                break;
            default:
                break;
            }


            float widthStep = renderer->GetWindowDimensions().x / static_cast<float>(MAX_MAZE_WIDTH_IN_TILES);
            float heightStep = renderer->GetWindowDimensions().y / static_cast<float>(MAX_MAZE_WIDTH_IN_TILES);
            float step = std::min(widthStep, heightStep);

            currMazeObj.SetPosition(Vec2(static_cast<float>(j) * step, static_cast<float>(i) * step));
            /*currMazeObj.SetScale(Vec2(widthStep / static_cast<float>(currMazeObj.GetTexture()->GetWidth()),
                heightStep / static_cast<float>(currMazeObj.GetTexture()->GetHeight())));*/

            renderer->Draw(&currMazeObj);
        }
    }
}

void Maze::ParseMazeImage(const char* mazeFilePath, const char cWall, const char cFloor)
{
    std::ifstream mazeImageFile(mazeFilePath);

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

    for (size_t i = 0; i < mazeString.size(); ++i)
    {
        if (mazeString[i] == cWall)
            m_mazeGrid.emplace_back(CellType::WALL);
        else if (mazeString[i] == cFloor)
            m_mazeGrid.emplace_back(CellType::FLOOR);
        else
            m_mazeGrid.emplace_back(CellType::UNKNOWN);
    }

    mazeImageFile.close();
}