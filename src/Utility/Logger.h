#pragma once

#include <iostream>
#include <format>

// Define Logger macro for different builds
#ifndef NDEBUG // Debug
#define LOG(msg, ...) (std::cout << "[LOGGER]: " << std::format(msg, ##__VA_ARGS__) << std::endl)
#else // Not debug
#define LOG(msg, ...)
#endif