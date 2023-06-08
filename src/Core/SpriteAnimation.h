#pragma once

#include <vector>
#include "Sprite.h"
#include "Texture.h"

class SpriteAnimation
{
public:
	SpriteAnimation() = default;

	bool Init(Sprite* sprite);
	void OnUpdate(float timestep);
	void AddTexture(Texture* texture);

private:
	Sprite* m_sprite = nullptr;
	std::vector<Texture*> m_textures;
};