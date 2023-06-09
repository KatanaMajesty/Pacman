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
	m_window->SetViewport(framedesc.viewportLeft, framedesc.viewportTop, framedesc.viewportBottom, framedesc.viewportRight);
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

static sf::PrimitiveType GetSFMLPrimitiveType(PrimitiveType type)
{
	switch (type)
	{
	case PrimitiveType::POINTS: return sf::PrimitiveType::Points;
	case PrimitiveType::LINES: return sf::PrimitiveType::Lines;
	case PrimitiveType::TRIANGLES: return sf::PrimitiveType::Triangles;
	default: ASSERT(false && "Cannot determine primitive type"); return sf::PrimitiveType::Triangles;
	}
}

void Renderer::Draw(const Vertex* vertices, uint32_t numVertices, PrimitiveType primitive)
{
	sf::RenderWindow* rw = reinterpret_cast<sf::RenderWindow*>(m_window->GetHandle());
	rw->draw(vertices, numVertices, GetSFMLPrimitiveType(primitive));
}

void Renderer::Draw(const Sprite* sprite)
{
	sf::RenderWindow* rw = reinterpret_cast<sf::RenderWindow*>(m_window->GetHandle());
	rw->draw(sprite->m_sprite);
}

//void Renderer::Draw(const TextManager* text)
//{
//	sf::RenderWindow* rw = reinterpret_cast<sf::RenderWindow*>(m_window->GetHandle());
//	rw->draw(text->m_text);
//}

Color ColorOf(const Vec3& rgb, float alpha)
{
	sf::Uint8 r = static_cast<sf::Uint8>(rgb.x * 255.0f);
	sf::Uint8 g = static_cast<sf::Uint8>(rgb.y * 255.0f);
	sf::Uint8 b = static_cast<sf::Uint8>(rgb.z * 255.0f);
	sf::Uint8 a = static_cast<sf::Uint8>(alpha * 255.0f);
	return Color(r, g, b, a);
}
