#include <memory>
#include <array>
#include "Core/Window.h"
#include "Core/Renderer.h"
#include "Core/TextureLibrary.h"
#include "Utility/Logger.h"
#include "Utility/Clock.h"
#include "Utility/FileSystem.h"
#include "Game/TextureAtlas.h"

int main()
{
	Window window(800, 600, "Hello, Window");
	window.Open();

	Renderer renderer;
	renderer.Init(&window);

	TextureAtlas atlas;
	
	uint32_t w = 64;
	std::array<Sprite, TextureType::NUM_TEXTURES> sprites;
	for (uint32_t i = 0; i < TextureType::NUM_TEXTURES; ++i)
	{
		Sprite& sprite = sprites[i];
		sprite.SetTexture(atlas.GetAtlasPosition((TextureType)i));
		uint32_t x = i % 4;
		uint32_t y = i / 4;
		sprite.SetPosition(Vec2(x * w, y * w));
		sprite.SetScale(2.0f);
	}

	Clock clock;
	clock.start();
	while (!window.ShouldClose())
	{
		window.PollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		renderer.BeginFrame(FrameDesc());
		{
			for (Sprite& s : sprites)
				renderer.Draw(&s);
		}
		renderer.EndFrame();
	}
	clock.stop();
}