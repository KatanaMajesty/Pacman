#pragma once

#include "../Core/Texture.h"

enum TextureType // Changed to enum class for stronger typing
{
    DUNGEON_TILE,
    DUNGEON_WALL1,
    DUNGEON_WALL2,
    DUNGEON_WALL3,
    SLIME_GREEN_IDLE,
    SLIME_GREEN_JUMPING,
    SLIME_BLUE_IDLE,
    SLIME_BLUE_JUMPING,
    SLIME_RED_IDLE,
    SLIME_RED_JUMPING,
    SLIME_YELLOW_IDLE,
    SLIME_YELLOW_JUMPING,
    SLIME_PURPLE_IDLE,
    SLIME_PURPLE_JUMPING,
    COIN,
    WAND,
    NUM_TEXTURES,
};

class TextureAtlas
{
public:
    Texture* GetAtlasPosition(TextureType textureType);
};
