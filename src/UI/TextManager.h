#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "TextComponent.h"
#include "../Utility/Math.h"
#include "../Utility/FileSystem.h"

enum TextFont
{
    DEFAULT_FONT,
};

class TextManager
{
public:
    TextManager();

    static TextManager& Get();
    
    bool LoadFont(TextFont font, const std::string& filename);
    TextComponent* CreateText(const std::string& str, uint32_t fontsize, const Vec2& pos, TextFont font);
    TextComponent* CreateText(uint32_t fontsize, const Vec2& pos, TextFont font);

protected:
    sf::Font* GetFont(TextFont font);

    std::unordered_map<TextFont, std::unique_ptr<sf::Font>> m_fonts;
    std::vector<std::unique_ptr<TextComponent>> m_textComponents;
};