#pragma once

#include <memory>
#include <unordered_map>
#include "../Core/Sprite.h"
#include "../Core/SpriteAnimation.h"

class AnimationManager
{
public:
	AnimationManager() = default;

	void OnUpdate(float timestep);
	SpriteAnimation* CreateAnimation(const std::string& name);
	SpriteAnimation* GetAnimation(const std::string& name);

private:
	std::unordered_map<std::string, std::unique_ptr<SpriteAnimation>> m_animations;
};