#pragma once

#include <SFML/Graphics.hpp>
#include "Window.h"

using Vertex = sf::Vertex;
using PrimitiveType = sf::PrimitiveType;
using Vec2 = sf::Vector2f;
using Vec3 = sf::Vector3f;
using Color = sf::Color;

Color ColorOf(const Vec3& rgb, float alpha);

struct FrameDesc
{
	float clearcolor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
};

class Renderer
{
public:
	bool Init(Window* window);

	void BeginFrame(const FrameDesc& framedesc);
	void EndFrame();
	void Draw(const Vertex* vertices, uint32_t numVertices, PrimitiveType primitive);

private:
	Window* m_window = nullptr;
};