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
	BoundingBox(const Vec2& min, const Vec2& max) :m_min(min), m_max(max) {};

	bool Collide(const BoundingBox& Bounds);
private:
	Vec2 m_max;
	Vec2 m_min;
};