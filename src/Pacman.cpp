#include <memory>
#include <array>
#include "Core/Window.h"
#include "Core/Renderer.h"
#include "Core/TextureLibrary.h"
#include "Utility/Logger.h"
#include "Utility/Clock.h"
#include "Utility/FileSystem.h"
#include "Game/TextureAtlas.h"
#include "Game/Level.h"

int main()
{
	Window window(800, 600, "Hello, Window");
	window.Open();

	Renderer renderer;
	renderer.Init(&window);

	TextureAtlas atlas;

	Level level("Assets/Maze.txt");
	level.SetRenderer(&renderer);
	level.SetMazeWallTexture(atlas.GetTexture(TextureType::TEXTURE_DUNGEON_TILE));
	level.SetMazeFloorTexture(atlas.GetTexture(TextureType::TEXTURE_DUNGEON_WALL1));
	
	Clock clock;
	clock.start();
	while (!window.ShouldClose())
	{
		window.PollEvents();

		renderer.BeginFrame(FrameDesc());
		level.Draw();
		renderer.EndFrame();
	}
	clock.stop();
}