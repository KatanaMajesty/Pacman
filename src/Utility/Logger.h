#pragma once

#include <iostream>
#include <format>

// Define Logger macro for different builds
#ifndef NDEBUG // Debug
#define LOG(msg, ...) (std::cout << "[LOGGER]: " << std::format(msg, ##__VA_ARGS__) << std::endl)
#else // Not debug
#define LOG(msg, ...)
#endif

#include <cassert>

#ifndef NDEBUG // Debug
#define ASSERT(...) (assert(__VA_ARGS__))
#else // Not debug
#define ASSERT(...)
#endif