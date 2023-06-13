#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using Vertex = sf::Vertex;
using Vec2 = sf::Vector2f;
using Vec3 = sf::Vector3f;
using Color = sf::Color;

enum class Direction
{
	DIRECTION_UP, // W
	DIRECTION_LEFT, // A
	DIRECTION_DOWN, // S
	DIRECTION_RIGHT, // D
};

struct BoundingBox
{
	BoundingBox() = default;
	BoundingBox(const Vec2& min, const Vec2& max) 
		: min(min)
		, max(max) 
	{
	};
	BoundingBox(const Vec2& min, float width, float height)
		: min(min)
		, max(min + Vec2(width, height))
	{
	}
	BoundingBox(const Vec2& pos, float radius)
		: min(pos - Vec2(radius / 2.0f, radius / 2.0f))
		, max(pos + Vec2(radius / 2.0f, radius / 2.0f))
	{
	}

	bool Collide(const BoundingBox& Bounds) const;

	Direction GetCollisionDirection(const BoundingBox& other) const;

	Vec2 max;
	Vec2 min;
};

inline constexpr Direction GetOppositeDirection(Direction direction)
{
	switch (direction)
	{
	case Direction::DIRECTION_UP: return Direction::DIRECTION_DOWN;
	case Direction::DIRECTION_LEFT: return Direction::DIRECTION_RIGHT;
	case Direction::DIRECTION_DOWN: return Direction::DIRECTION_UP;
	case Direction::DIRECTION_RIGHT: return Direction::DIRECTION_LEFT;
	default: return (Direction)-1;
	}
}

inline Vec2 VecFromDirection(Direction direction)
{
	switch (direction)
	{
	case Direction::DIRECTION_UP: return Vec2(0.0f, -1.0f);
	case Direction::DIRECTION_LEFT: return Vec2(-1.0f, 0.0f);
	case Direction::DIRECTION_DOWN: return Vec2(0.0f, 1.0f);
	case Direction::DIRECTION_RIGHT: return Vec2(1.0f, 0.0f);
	default: return Vec2(0.0f, 0.0f);
	}
}

static uint32_t Manhattan(const Vec2& lhs, const Vec2& rhs)
{
	Vec2 delta{ abs(lhs.x - rhs.x), abs(lhs.y - rhs.y)};
	return static_cast<uint32_t>(delta.x + delta.y);
}