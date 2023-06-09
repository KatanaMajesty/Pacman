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

	EventBus& eventBus = EventBus::Get();

	TextureAtlas& atlas = TextureAtlas::Get();

	TextManager& text = TextManager::Get();

	Level level(&renderer);
	level.Init((FileSystem::Get().GetAssetsPath() / "Maze.txt").string());
	
	Clock clock;
	clock.start();

	float lastFrame = 0.0f;
	while (!window.ShouldClose())
	{
		window.PollEvents();
		//window.SetView(800.0f, 800.0f);

		float elapsed = clock.elapsed();
		float timestep = elapsed - lastFrame;
		lastFrame = elapsed;
		AnimationManager::Get().OnUpdate(timestep);

		FrameDesc frameDesc;
		frameDesc.clearcolor[0] = 0.0f;
		frameDesc.clearcolor[1] = 1.0f;
		frameDesc.clearcolor[2] = 0.0f;
		frameDesc.clearcolor[3] = 1.0f;
		/*frameDesc.viewportLeft = 0.0f;
		frameDesc.viewportTop = 0.0f;
		frameDesc.viewportBottom = 0.5f;
		frameDesc.viewportRight = 0.5f;*/

		//text.PrintText("Bruh", { 300,300 });

		renderer.BeginFrame(frameDesc);
		level.OnUpdate(timestep);
		renderer.EndFrame();
	}
	clock.stop();
}