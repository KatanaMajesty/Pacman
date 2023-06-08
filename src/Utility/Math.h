#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using Vertex = sf::Vertex;
using Vec2 = sf::Vector2f;
using Vec3 = sf::Vector3f;
using Color = sf::Color;

struct BoundingBox
{
	BoundingBox() = default;
	BoundingBox(const Vec2& min, const Vec2& max) 
		: min(min)
		, max(max) 
	{
	};
	BoundingBox(const Vec2& pos, float width, float height)
		: min(pos - Vec2(width, height))
		, max(pos + Vec2(width, height))
	{
	}

	bool Collide(const BoundingBox& Bounds);

	Vec2 max;
	Vec2 min;
};