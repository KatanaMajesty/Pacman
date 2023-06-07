#pragma once

#include <chrono>

class Clock
{
public:
	// Starts a clock
	void start();

	// Stops clock, resets it to the initial state
	void stop();

	// Returns amount of seconds elapsed since last call to Clock::start
	float elapsed() const;

private:
	bool m_started = false;
	std::chrono::system_clock::time_point m_startPoint = {};
};