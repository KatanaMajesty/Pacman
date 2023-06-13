#pragma once

#include <chrono>

class Clock
{
public:
	Clock() noexcept;
	float Mark() noexcept;
	float Peek() noexcept;

private:
	std::chrono::steady_clock::time_point m_last;
};