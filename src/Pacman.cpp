#include <memory>
#include "Core/Window.h"
#include "Core/Renderer.h"
#include "Core/TextureLibrary.h"
#include "Utility/Logger.h"
#include "Utility/Clock.h"
#include "Utility/FileSystem.h"

int main()
{
	Window window(800, 600, "Hello, Window");
	window.Open();

	Renderer renderer;
	renderer.Init(&window);

	FileSystem& filesystem = FileSystem::Get();
	Texture* texture = TextureLibrary::Get().CreateTexture((filesystem.GetAssetsPath() / "pacman1.png").string());
	if (!texture)
	{
		LOG("Failed to create a texture!");
	}

	Clock clock;
	clock.start();
	while (!window.ShouldClose())
	{
		window.PollEvents();

		renderer.BeginFrame(FrameDesc());
		{
			// Draw stuff that we need with renderer
			uint32_t width = window.GetWidth();
			uint32_t height = window.GetHeight();
			Vec2 center(width / 2.0f, height / 2.0f);

			float t = std::fmod(clock.elapsed() / 10.0f, 60.0f);
			float v1 = std::fmod(60.0f - t, 1.0f);
			float v2 = std::fmod(60.0f - t, 0.66f);
			float v3 = std::fmod(60.0f - t, 0.33f);

			Vec3 colors[3];
			colors[0] = Vec3(v1, v2, v3);
			colors[1] = Vec3(v2, v1, v3);
			colors[2] = Vec3(v3, v2, v1);

			Vertex triangle[3];
			triangle[0] = Vertex(center - Vec2(200.0f, -100.0f), ColorOf(colors[0], 1.0f));
			triangle[1] = Vertex(center - Vec2(-200.0f, -100.0f), ColorOf(colors[1], 1.0f));
			triangle[2] = Vertex(center - Vec2(0.0f, 100.0f), ColorOf(colors[2], 1.0f));
			renderer.Draw(triangle, 3, PrimitiveType::TRIANGLES);
		}
		renderer.EndFrame();
	}
	clock.stop();
}