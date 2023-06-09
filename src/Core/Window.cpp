#include "Window.h"

#include "../Utility/Logger.h"

Window::Window(uint32_t width, uint32_t height, const std::string& title)
	: m_width(width)
	, m_height(height)
	, m_title(title)
{
}

Window::~Window()
{
}

bool Window::Open()
{
	// If window was never created before - we allocate it
	if (!m_window)
	{
		m_window.reset(new sf::RenderWindow(sf::VideoMode(m_width, m_height), m_title));
		LOG("Allocating a window {}", m_title);
		return true;
	}

	m_window->close();
	m_window->create(sf::VideoMode(m_width, m_height), m_title);
	return true;
}

bool Window::Close()
{
	if (!m_window)
	{
		LOG("Cannot close the window {} as it is not opened", m_title);
		return false;
	}

	m_window->close();
	return true;
}

void Window::PollEvents()
{
	if (!m_window)
		return;

	// check all the window's events that were triggered since the last iteration of the loop
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		// "close requested" event: we close the window
		if (event.type == sf::Event::Closed)
			m_window->close();

		// catch the resize events
		if (event.type == sf::Event::Resized)
		{
			m_width = static_cast<float>(event.size.width);
			m_height = static_cast<float>(event.size.height);

			sf::View view;
			view.setCenter(m_width / 2.0f, m_height / 2.0f);
			view.setSize(m_width, m_height);
			m_window->setView(view);
		}
	}
}

bool Window::ShouldClose() const
{
	if (!m_window)
		return true;

	return !m_window->isOpen();
}

void Window::SetViewport(float left, float top, float bottom, float right) const
{
	sf::View view;
	sf::FloatRect rect;
	rect.top = top;
	rect.left = left;
	rect.width = right - left;
	rect.height = -top + bottom;
	view.setViewport(rect);
	m_window->setView(view);
}
