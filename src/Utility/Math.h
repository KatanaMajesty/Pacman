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
		/*: min(pos - Vec2(width / 2.0f, height / 2.0f))
		, max(pos + Vec2(width / 2.0f, height / 2.0f))*/
		: min(Vec2(pos.x, pos.y))
		, max(Vec2(pos.x + width, pos.y + height))
	{
	}
	BoundingBox(const Vec2& pos, float radius)
		: min(pos - Vec2(radius / 2.0f, radius / 2.0f))
		, max(pos + Vec2(radius / 2.0f, radius / 2.0f))
	{
	}

	bool Collide(const BoundingBox& Bounds) const;

	Vec2 max;
	Vec2 min;
};

enum Direction
{
	DIRECTION_UP, // W
	DIRECTION_LEFT, // A
	DIRECTION_DOWN, // S
	DIRECTION_RIGHT, // D
};

inline constexpr Direction GetOppositeDirection(Direction direction)
{
	switch (direction)
	{
	case DIRECTION_UP: return DIRECTION_DOWN;
	case DIRECTION_LEFT: return DIRECTION_RIGHT;
	case DIRECTION_DOWN: return DIRECTION_UP;
	case DIRECTION_RIGHT: return DIRECTION_LEFT;
	default: return (Direction)-1;
	}
}

inline Vec2 VecFromDirection(Direction direction)
{
	switch (direction)
	{
	case DIRECTION_UP: return Vec2(0.0f, -1.0f);
	case DIRECTION_LEFT: return Vec2(-1.0f, 0.0f);
	case DIRECTION_DOWN: return Vec2(0.0f, 1.0f);
	case DIRECTION_RIGHT: return Vec2(1.0f, 0.0f);
	default: return Vec2(0.0f, 0.0f);
	}
}

static uint32_t Manhattan(const Vec2& lhs, const Vec2& rhs)
{
	Vec2 delta{ abs(lhs.x - rhs.x), abs(lhs.y - rhs.y)};
	return static_cast<uint32_t>(delta.x + delta.y);
}