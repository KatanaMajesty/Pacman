#include "TextureAtlas.h"

#include <array>
#include "../Core/TextureLibrary.h"
#include "../Utility/FileSystem.h"
#include "../Utility/Logger.h"

// Define a map to store the top and left positions of textures in the atlas
std::array g_atlasPositions = {
    std::pair<uint32_t, uint32_t>{0, 0},
    std::pair<uint32_t, uint32_t>{0, 1},
    std::pair<uint32_t, uint32_t>{0, 2},
    std::pair<uint32_t, uint32_t>{0, 3},
    std::pair<uint32_t, uint32_t>{1, 0},
    std::pair<uint32_t, uint32_t>{1, 1},
    std::pair<uint32_t, uint32_t>{1, 2},
    std::pair<uint32_t, uint32_t>{1, 3},
    std::pair<uint32_t, uint32_t>{2, 0},
    std::pair<uint32_t, uint32_t>{2, 1},
    std::pair<uint32_t, uint32_t>{2, 2},
    std::pair<uint32_t, uint32_t>{2, 3},
    std::pair<uint32_t, uint32_t>{3, 0},
    std::pair<uint32_t, uint32_t>{3, 1},
    std::pair<uint32_t, uint32_t>{3, 2},
    std::pair<uint32_t, uint32_t>{3, 3},
    std::pair<uint32_t, uint32_t>{4, 0},
    std::pair<uint32_t, uint32_t>{4, 1},
    std::pair<uint32_t, uint32_t>{4, 2},
    std::pair<uint32_t, uint32_t>{4, 3}
};

TextureAtlas::TextureAtlas()
    : m_textureWidth(32)
    , m_textureHeight(32)
{
}

Texture* TextureAtlas::GetTexture(TextureType textureType)
{
    static std::string filePath = (FileSystem::Get().GetAssetsPath() / "atlas.png").string();

    ASSERT(textureType < g_atlasPositions.size());
    if (textureType >= g_atlasPositions.size())
        return nullptr;

    auto [top, left] = g_atlasPositions[textureType];
    return TextureLibrary::Get().CreateTexture(filePath, m_textureHeight*top, m_textureWidth*left, m_textureWidth, m_textureHeight);
}