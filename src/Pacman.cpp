#include "Window.h"
#include "Renderer.h"

int main()
{
	Window window(800, 600, "Hello, Window");
	window.Open();

	Renderer renderer;
	renderer.Init(&window);

	while (!window.ShouldClose())
	{
		window.PollEvents();
		// Draw stuff that we need with renderer
	}
}