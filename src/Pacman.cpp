#include <memory>
#include <array>
#include "Core/Window.h"
#include "Core/Renderer.h"
#include "Core/TextureLibrary.h"
#include "Utility/Logger.h"
#include "Utility/Clock.h"
#include "Utility/FileSystem.h"
#include "Game/AnimationManager.h"
#include "Game/TextureAtlas.h"
#include "Game/Level.h"

int main()
{
	Window window(800, 600, "Hello, Window");
	window.Open();

	Renderer renderer;
	renderer.Init(&window);

	TextureAtlas& atlas = TextureAtlas::Get();

	Level level("Assets/Maze.txt");
	level.SetRenderer(&renderer);
	level.SetMazeWallTexture(atlas.GetTexture(TextureType::TEXTURE_DUNGEON_TILE));
	level.SetMazeFloorTexture(atlas.GetTexture(TextureType::TEXTURE_DUNGEON_WALL1));
	
	Sprite sprite;
	sprite.SetScale(4.0f);
	sprite.SetPosition(Vec2(400.0f, 300.0f));

	SpriteAnimation* animation = AnimationManager::Get().CreateAnimation("ANIM_YELLOW_SLIME");
	animation->AddTexture(atlas.GetTexture(TextureType::TEXTURE_SLIME_YELLOW_IDLE));
	animation->AddTexture(atlas.GetTexture(TextureType::TEXTURE_SLIME_YELLOW_JUMPING));
	animation->Init(&sprite, 0.5f);

	Clock clock;
	clock.start();

	float lastFrame = 0.0f;
	while (!window.ShouldClose())
	{
		window.PollEvents();

		float elapsed = clock.elapsed();
		float timestep = elapsed - lastFrame;
		lastFrame = elapsed;
		AnimationManager::Get().OnUpdate(timestep);

		renderer.BeginFrame(FrameDesc());
		
		level.Draw();
		renderer.Draw(&sprite);

		renderer.EndFrame();
	}
	clock.stop();
}