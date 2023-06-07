#include "Texture.h"

#include "../Utility/Logger.h"

Texture* Texture::CreateTexture(const std::string& filepath)
{
	Texture* texture = new Texture();
	if (!texture->Init(filepath))
	{
		delete texture;
		return nullptr;
	}
	return texture;
}

bool Texture::Init(const std::string& filepath)
{
	sf::IntRect rect;
	if (!m_texture.loadFromFile(filepath, rect))
	{
		LOG("Failed to load a texture from a path {}", filepath);
		return false;
	}

	return true;
}
