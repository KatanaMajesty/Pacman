#include <pch.h>

TextManager::TextManager()
{
    LoadFont(TextFont::DEFAULT_FONT, "Font.ttf");
}

TextManager& TextManager::Get()
{
    static TextManager instance;
    return instance;
}

bool TextManager::LoadFont(TextFont font, const std::string& filename)
{
    FileSystem& fs = FileSystem::Get();
    std::string filepath = (fs.GetAssetsPath() / filename).string();
   
    sf::Font* f = GetFont(font);
    if (f)
        return true;

    f = new sf::Font();
    if (!f->loadFromFile(filepath))
    {
        LOG("Failed to load a font {}", filepath);
        delete f;
        return false;
    }

    m_fonts[font] = std::unique_ptr<sf::Font>(f);
    return true;
}

TextComponent* TextManager::CreateText(const std::string& str, uint32_t fontsize, const Vec2& pos, TextFont font)
{
    sf::Font* sfFont = GetFont(font);
    if (!sfFont)
        return nullptr;

    TextComponent* text = new TextComponent();
    if (!text->Init(str, fontsize, pos, sfFont))
    {
        LOG("Failed to init text component");
        delete text;
        return nullptr;
    }

    return m_textComponents.emplace_back(std::unique_ptr<TextComponent>(text)).get();
}

TextComponent* TextManager::CreateText(uint32_t fontsize, const Vec2& pos, TextFont font)
{
    return this->CreateText("???", fontsize, pos, font);
}

sf::Font* TextManager::GetFont(TextFont font)
{
    auto it = m_fonts.find(font);
    return it == m_fonts.end() ? nullptr : it->second.get();
}
