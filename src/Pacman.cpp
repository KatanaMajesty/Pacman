#include "pch.h"

int main()
{
	try
	{
		return App().Go();
	}
	catch (const std::exception& e)
	{
		LOG("Standard Exception: {}", e.what());
	}
	catch (...)
	{
		LOG("Unknown Exception: No details available");
	}
}