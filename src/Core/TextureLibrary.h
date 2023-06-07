#pragma once

#include <memory>
#include <unordered_map>
#include "Texture.h"

// Texture factory
class TextureLibrary
{
private:
	TextureLibrary() = default;

public:
	TextureLibrary(const TextureLibrary&) = delete;
	TextureLibrary& operator=(const TextureLibrary&) = delete;

	static TextureLibrary& Get();

	// Allocates (and manages the allocated memory) the texture from a file with a specified offset
	Texture* CreateTexture(const std::string& filepath, uint32_t top = 0, uint32_t left = 0, uint32_t width = 0, uint32_t height = 0);

private:
	// Loads an image (and caches) from a filepath or gets a cached one, if any
	sf::Image* GetImage(const std::string& filepath);

	std::unordered_map<std::string, std::unique_ptr<sf::Image>> m_imageCache;
	std::vector<std::unique_ptr<Texture>> m_textures;
};