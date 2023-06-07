#include "TextureAtlas.h"

#include <vector>
#include <array>
#include "../Utility/FileSystem.h"

#include "../Core/TextureLibrary.h"


// Define a map to store the top and left positions of textures in the atlas
std::array atlasPositions = {
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

Texture* Atlas::GetAtlasPosition(TextureType textureType)
{
    FileSystem& filesystem = FileSystem::Get();
    TextureLibrary& textureLibrary = TextureLibrary::Get();
    std::string filePath = (filesystem.GetAssetsPath() / "atlas.png").string();
    static constexpr uint32_t textureSize = 32;

    if (textureType >= atlasPositions.size())
    {
        return nullptr;
    }

    auto [top, left] = atlasPositions[textureType];

    return textureLibrary.CreateTexture(filePath, top, left, textureSize, textureSize);;
}