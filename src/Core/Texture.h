#pragma once

#include <string>
#include <SFML/Graphics/Texture.hpp>

class Texture
{
public:
	Texture() = default;
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;

	// Factory method
	static Texture* CreateTexture(const std::string& filepath);

	bool Init(const std::string& filepath);
	uint32_t GetWidth() const { m_texture.getSize().x; }
	uint32_t GetHeight() const { m_texture.getSize().y; }

private:
	sf::Texture m_texture;
};