#include "Clock.h"

using namespace std::chrono;

void Clock::start()
{
	m_startPoint = system_clock::now();
	m_started = true;
}

void Clock::stop()
{
	m_started = false;
	m_startPoint = {};
}

float Clock::elapsed() const
{
	if (!m_started)
		return 0.0f;

	system_clock::time_point currentTime = system_clock::now();
	duration<float> elapsed = duration_cast<duration<float>>(currentTime - m_startPoint);
	return elapsed.count();
}