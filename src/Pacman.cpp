#include <memory>
#include <array>
#include "Core/Window.h"
#include "Core/Renderer.h"
#include "Core/TextureLibrary.h"
#include "Utility/Logger.h"
#include "Audio/AudioManager.h"
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

	Level level(&renderer);
	level.Init((FileSystem::Get().GetAssetsPath() / "Maze.txt").string());
	
	Sprite sprite;
	sprite.SetScale(4.0f);
	sprite.SetPosition(Vec2(400.0f, 300.0f));

	SpriteAnimation* animation = AnimationManager::Get().CreateAnimation("ANIM_YELLOW_SLIME");
	animation->AddTexture(atlas.GetTexture(TextureType::TEXTURE_SLIME_YELLOW_IDLE));
	animation->AddTexture(atlas.GetTexture(TextureType::TEXTURE_SLIME_YELLOW_JUMPING));
	animation->Init(&sprite, 0.5f);

	Clock clock;
	clock.start();

	AudioManager& audio = AudioManager::Get();
	audio.PlaySound(AUDIO_COIN_COLLECT);
	audio.PlaySound(AUDIO_PLAYER_DEATH);

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
		frameDesc.viewportLeft = 0.25f;
		frameDesc.viewportTop = 0.25f;
		frameDesc.viewportBottom = 0.75f;
		frameDesc.viewportRight = 0.75f;

		renderer.BeginFrame(frameDesc);

		level.OnUpdate(timestep);
		renderer.Draw(&sprite);

		renderer.EndFrame();
	}
	clock.stop();
}