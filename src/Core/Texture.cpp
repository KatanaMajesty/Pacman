#include <pch.h>

bool Texture::Init(const sf::Image* image, uint32_t top, uint32_t left, uint32_t width, uint32_t height)
{
	sf::IntRect rect;
	rect.top = top;
	rect.left = left;
	rect.width = width;
	rect.height = height;

	if (!m_texture.loadFromImage(*image, rect))
	{
		LOG("Failed to load a texture from an image");
		return false;
	}

	return true;
}

void Texture::Swap(Texture* texture)
{
	m_texture.swap(texture->m_texture);
}
