#include "Renderer.h"

#include <SFML/Graphics.hpp>
#include "../Utility/Logger.h"

bool Renderer::Init(Window* window)
{
	if (!window)
	{
		LOG("(Renderer) Provided window is nullptr");
		return false;
	}
	m_window = window;
	return true;
}

void Renderer::BeginFrame(const FrameDesc& framedesc)
{
	sf::RenderWindow* rw = reinterpret_cast<sf::RenderWindow*>(m_window->GetHandle());
	sf::Uint8 r = static_cast<sf::Uint8>(framedesc.clearcolor[0] * 255.0f);
	sf::Uint8 g = static_cast<sf::Uint8>(framedesc.clearcolor[1] * 255.0f);
	sf::Uint8 b = static_cast<sf::Uint8>(framedesc.clearcolor[2] * 255.0f);
	sf::Uint8 a = static_cast<sf::Uint8>(framedesc.clearcolor[3] * 255.0f);
	rw->clear(sf::Color(r, g, b, a));
}

void Renderer::EndFrame()
{
	sf::RenderWindow* rw = reinterpret_cast<sf::RenderWindow*>(m_window->GetHandle());
	rw->display();
}

void Renderer::Draw(const Vertex* vertices, uint32_t numVertices, PrimitiveType primitive)
{
	sf::RenderWindow* rw = reinterpret_cast<sf::RenderWindow*>(m_window->GetHandle());
	rw->draw(vertices, numVertices, primitive);
}

Color ColorOf(const Vec3& rgb, float alpha)
{
	sf::Uint8 r = static_cast<sf::Uint8>(rgb.x * 255.0f);
	sf::Uint8 g = static_cast<sf::Uint8>(rgb.y * 255.0f);
	sf::Uint8 b = static_cast<sf::Uint8>(rgb.z * 255.0f);
	sf::Uint8 a = static_cast<sf::Uint8>(alpha * 255.0f);
	return Color(r, g, b, a);
}
