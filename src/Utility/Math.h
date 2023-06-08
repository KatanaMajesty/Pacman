#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using Vertex = sf::Vertex;
using Vec2 = sf::Vector2f;
using Vec3 = sf::Vector3f;
using Color = sf::Color;

class BoundingBox
{
public:
	BoundingBox() = default;

	void Init(uint32_t height, uint32_t width){
		m_height = height;
		m_width = width;
	}

private:
	uint32_t m_height = 0;
	uint32_t m_width = 0;
};