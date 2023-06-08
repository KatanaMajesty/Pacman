#pragma once

#include <cstdint>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>

class Window
{
public:
	Window(uint32_t width, uint32_t height, const std::string& title);
	~Window();

	bool Open();
	bool Close();
	void PollEvents();
	bool ShouldClose() const;
	void SetViewport(float left, float top, float bottom, float right) const;

	constexpr uint32_t GetWidth() const { return m_width; }
	constexpr uint32_t GetHeight() const { return m_height; }
	const std::string& GetTitle() const { return m_title; }

	void* GetHandle() { return m_window.get(); }

private:
	uint32_t m_width;
	uint32_t m_height;
	std::string m_title;
	std::unique_ptr<sf::RenderWindow> m_window;
};