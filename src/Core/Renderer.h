#pragma once

#include "Window.h"
#include "Sprite.h"
#include "../Utility/Math.h"

// Primitive types, that are used in the project
enum PrimitiveType
{
	POINTS,
	LINES,
	TRIANGLES
};

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
	void Draw(const Sprite* sprite);

	inline const Vec2& GetWindowDimensions() const { return {static_cast<float>(m_window->GetWidth()), static_cast<float>(m_window->GetHeight())}; }

private:
	Window* m_window = nullptr;
};