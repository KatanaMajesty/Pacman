#pragma once

#include "../Utility/Math.h"
#include "../Utility/FileSystem.h"
#include <string>

class TextManager
{
public:
    TextManager();
    static TextManager& Get();
    void PrintText(std::string textToPrint, const Vec2& pos);
protected:
    friend class Renderer;
    friend class Level;
    sf::Font m_font;
    sf::Text m_text;
    void SetFont(const std::string& fontPath);
    void SetCharacterSize(unsigned int characterSize);
    void SetColor(const sf::Color& color);
};