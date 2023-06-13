#include "pch.h"

using namespace std::chrono;

Clock::Clock() noexcept
{
	m_last = steady_clock::now();
}

float Clock::Mark() noexcept
{
	const auto old = m_last;
	m_last = steady_clock::now();
	const duration<float> frameTime = m_last - old;
	return frameTime.count();
}

float Clock::Peek() noexcept
{
	return duration<float>(steady_clock::now() - m_last).count();
}