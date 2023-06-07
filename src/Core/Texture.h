#pragma once

#include <string>
#include <SFML/Graphics/Texture.hpp>

class Texture
{
public:
	Texture() = default;
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;

	bool Init(const sf::Image* image, uint32_t top = 0, uint32_t left = 0, uint32_t width = 0, uint32_t height = 0);
	void Swap(Texture* texture);
	uint32_t GetWidth() const { m_texture.getSize().x; }
	uint32_t GetHeight() const { m_texture.getSize().y; }
	inline void* GetHandle() { return &m_texture; }

private:
	sf::Texture m_texture;
};