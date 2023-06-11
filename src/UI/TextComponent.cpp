#include <pch.h>

bool TextComponent::Init(const std::string& str, uint32_t size, const Vec2& pos, sf::Font* font)
{
	m_fontSize = size;
	m_font = font;
	m_string = str;
	m_text.setString(str);
	m_text.setFont(*font);
	m_text.setPosition(pos);
	m_text.setCharacterSize(size);
	return true;
}

bool TextComponent::Init(uint32_t size, const Vec2& pos, sf::Font* font)
{
	return this->Init("???", size, pos, font);
}
