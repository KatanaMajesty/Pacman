#include "TextureAtlas.h"

#include <array>
#include "../Core/TextureLibrary.h"
#include "../Utility/FileSystem.h"
#include "../Utility/Logger.h"

// Define a map to store the top and left positions of textures in the atlas
std::array g_atlasPositions = {
    std::pair<uint32_t, uint32_t>{0, 0},
    std::pair<uint32_t, uint32_t>{0, 32},
    std::pair<uint32_t, uint32_t>{0, 64},
    std::pair<uint32_t, uint32_t>{0, 96},
    std::pair<uint32_t, uint32_t>{32, 0},
    std::pair<uint32_t, uint32_t>{32, 32},
    std::pair<uint32_t, uint32_t>{32, 64},
    std::pair<uint32_t, uint32_t>{32, 96},
    std::pair<uint32_t, uint32_t>{64, 0},
    std::pair<uint32_t, uint32_t>{64, 32},
    std::pair<uint32_t, uint32_t>{64, 64},
    std::pair<uint32_t, uint32_t>{64, 96},
    std::pair<uint32_t, uint32_t>{96, 0},
    std::pair<uint32_t, uint32_t>{96, 32},
    std::pair<uint32_t, uint32_t>{96, 64},
    std::pair<uint32_t, uint32_t>{96, 96}
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
    return TextureLibrary::Get().CreateTexture(filePath, top, left, m_textureWidth, m_textureHeight);
}