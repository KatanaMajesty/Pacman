#include <memory>
#include <array>
#include "Audio/AudioManager.h"
#include "Core/Window.h"
#include "Core/Renderer.h"
#include "Core/TextureLibrary.h"
#include "Game/AnimationManager.h"
#include "Game/TextureAtlas.h"
#include "Game/Level.h"
#include "Utility/Logger.h"
#include "Utility/Clock.h"
#include "Utility/FileSystem.h"
#include "Utility/EventBus.h"
#include "UI/TextManager.h"

int main()
{
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

	Clock clock;
	clock.start();

	TextManager& text = TextManager::Get();

	TextureLibrary& library = TextureLibrary::Get();
	std::string filepath = (fs.GetAssetsPath() / "textbox.png").string();
	Sprite ui;
	Texture* t = library.CreateTexture(filepath);
	float vs = window.GetViewsize();
	float scaleX = vs / t->GetWidth();
	float scaleY = vs / t->GetHeight();
	ui.SetTexture(t);
	ui.SetScale(scaleX, scaleY);

	float lastFrame = 0.0f;
	while (!window.ShouldClose())
	{
		window.PollEvents();
		//window.SetView(800.0f, 800.0f);

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
		renderer.Draw(&ui);

		text.PrintText("bruh", { 0,0 });
		renderer.Draw(&text);

		renderer.EndFrame();
	}
	clock.stop();

	AudioManager::Deinit(); // Deinitialize the AudioManager
}