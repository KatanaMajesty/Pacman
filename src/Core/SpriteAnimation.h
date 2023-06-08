#pragma once

#include <vector>
#include "Sprite.h"
#include "Texture.h"

class SpriteAnimation
{
public:
	SpriteAnimation() = default;

	bool Init(Sprite* sprite, float interval);
	void OnUpdate(float timestep);
	void SetInterval(float interval) { m_interval = interval; }
	void AddTexture(Texture* texture);
	float GetUpdateInterval() const { return m_interval; }

private:
	Sprite* m_sprite = nullptr;
	float m_interval = 0.0f;
	float m_timeSinceLastTick = 0.0f;
	size_t m_currentTexture = 0;
	std::vector<Texture*> m_textures;
};