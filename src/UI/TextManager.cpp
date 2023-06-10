#include "TextManager.h"

TextManager::TextManager()
{
    // Initialize the font and text objects
    static std::string filepath = (FileSystem::Get().GetAssetsPath() / "Font.ttf").string();
    m_font.loadFromFile(filepath);
    m_text.setFont(m_font);
    m_text.setFillColor(Color::White);
    m_text.setCharacterSize(90);
}

TextManager& TextManager::Get()
{
    static TextManager instance;
    return instance;
}

void TextManager::PrintText(std::string textToPrint, const Vec2& pos)
{
    m_text.setString(textToPrint);
    m_text.setPosition(pos);
}


void TextManager::SetFont(const std::string& fontPath)
{
    m_font.loadFromFile(fontPath);
    m_text.setFont(m_font);
}

void TextManager::SetCharacterSize(unsigned int characterSize)
{
    m_text.setCharacterSize(characterSize);
}

void TextManager::SetColor(const sf::Color& color)
{
    m_text.setFillColor(color);
}
