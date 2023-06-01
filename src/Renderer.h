#pragma once

#include <SFML/Graphics.hpp>
#include "Window.h"

using Vertex = sf::Vertex;
using PrimitiveType = sf::PrimitiveType;

class Renderer
{
public:
	bool Init(Window* window) noexcept;
	void Draw(const Vertex* vertices, uint32_t numVertices, PrimitiveType primitive);
};