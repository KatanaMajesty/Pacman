#pragma once

#include <format>
#include <SFML/Graphics.hpp>
#include "../Utility/Math.h"

class TextComponent
{
public:
	bool Init(const std::string& str, uint32_t size, const Vec2& pos, sf::Font* font);
	bool Init(uint32_t size, const Vec2& pos, sf::Font* font);
	void SetScale(float x, float y) { m_text.setScale(Vec2(x, y)); }
	void SetPosition(const Vec2& pos) { m_text.setPosition(pos); }
	void AddPosition(const Vec2& pos) { m_text.setPosition(m_text.getPosition() + pos); }
	Vec2 GetPosition() const { return m_text.getPosition(); }
	inline float GetWidth() const { return m_text.getGlobalBounds().width; }
	inline float GetHeight() const { return m_text.getGlobalBounds().height; }
	uint32_t GetFontSize() const { return m_fontSize; }
	const std::string& GetString() const { return m_string; }
	const void* GetHandle() const { return &m_text; }

	template<typename... Args>
	void SetString(std::string_view str, Args&&... args)
	{
		m_string = std::vformat(str, std::make_format_args(std::forward<Args>(args)...));
		m_text.setString(m_string);
	}

private:
	sf::Font* m_font = nullptr;
	sf::Text m_text;
	uint32_t m_fontSize = 0;
	std::string m_string;
};