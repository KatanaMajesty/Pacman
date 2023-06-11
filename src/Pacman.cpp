#include <pch.h>
#include "Game/Level.h"

int main()
{
	RandomGenerator::SetSeed(0);

	Window window(800, 600, "Hello, Window");
	window.Open();

	Renderer renderer;
	renderer.Init(&window);

	if (!AudioManager::Init())
	{
		LOG("Failed to initialize Audio Manager");
		return 1;
	}

	FileSystem& fs = FileSystem::Get();
	TextureAtlas& atlas = TextureAtlas::Get();
	Level level(&renderer);
	level.Init((fs.GetAssetsPath() / "Maze2.txt").string());
	window.SetViewsize(level.GetMaze()->GetViewsize());

	UI ui(&renderer);
	ui.Init();

	Clock clock;
	clock.start();

	float lastFrame = 0.0f;
	while (!window.ShouldClose())
	{
		window.PollEvents();

		float elapsed = clock.elapsed();
		float timestep = elapsed - lastFrame;
		lastFrame = elapsed;

		FrameDesc frameDesc;
		frameDesc.clearcolor[0] = 0.0f;
		frameDesc.clearcolor[1] = 0.0f;
		frameDesc.clearcolor[2] = 0.0f;
		frameDesc.clearcolor[3] = 1.0f;

		renderer.BeginFrame(frameDesc);
		renderer.SetViewport(Vec2(0.1f, 0.0f), Vec2(0.9f, 0.8f));
		level.OnUpdate(timestep);

		renderer.SetViewport(Vec2(0.1f, 0.8f), Vec2(0.9f, 1.0f));
		ui.SetLevelInfo({ level.GetPlayer()->GetCollectedCoins(), level.GetOverallCoinsNumber(), level.GetPlayer()->GetHealth()});
		ui.OnUpdate(timestep);

		renderer.EndFrame();
	}
	clock.stop();

	AudioManager::Deinit(); // Deinitialize the AudioManager
}