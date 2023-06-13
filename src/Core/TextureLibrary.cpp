#include "pch.h"

TextureLibrary& TextureLibrary::Get()
{
	static TextureLibrary instance;
	return instance;
}

Texture* TextureLibrary::CreateTexture(const std::string& filepath, uint32_t top, uint32_t left, uint32_t width, uint32_t height)
{
	auto* image = GetImage(filepath);
	if (!image) // we should not get nullptr here. Means that the file does no exist.
		return nullptr;

	Texture* texture = new Texture();
	if (!texture->Init(image, top, left, width, height))
	{
		delete texture;
		return nullptr;
	}

	auto& ptr = m_textures.emplace_back(std::unique_ptr<Texture>(texture));
	return ptr.get();
}

sf::Image* TextureLibrary::GetImage(const std::string& filepath)
{
	auto it = m_imageCache.find(filepath);
	if (it == m_imageCache.end())
	{
		sf::Image* image = new sf::Image();
		if (!image->loadFromFile(filepath))
		{
			LOG("Failed to load an image from file {}", filepath);
			delete image;
			return nullptr;
		}
		auto [emplacedIterator, emplaced] = m_imageCache.emplace(filepath, std::unique_ptr<sf::Image>(image));
		ASSERT(emplaced && "Emplacement should not fail");
		it = emplacedIterator;
	}

	return it->second.get();
}
