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

	bool Open() noexcept;
	bool Close() noexcept;
	void PollEvents() noexcept;
	bool ShouldClose() const noexcept;

	constexpr uint32_t GetWidth() const noexcept { return m_width; }
	constexpr uint32_t GetHeight() const noexcept { return m_height; }
	const std::string& GetTitle() const noexcept { return m_title; }

	void* GetHandle() noexcept { return m_window.get(); }

private:
	uint32_t m_width;
	uint32_t m_height;
	std::string m_title;
	std::unique_ptr<sf::RenderWindow> m_window;
};