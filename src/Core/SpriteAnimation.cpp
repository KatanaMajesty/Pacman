#include "SpriteAnimation.h"

#include "../Utility/Logger.h"

bool SpriteAnimation::Init(Sprite* sprite, float interval)
{
	ASSERT(sprite && interval > 0.001f);
	ASSERT(m_textures.size() > 0);
	m_sprite = sprite;
	m_interval = interval;
	m_timeSinceLastTick = 0.0f;
	// we set current sprite's texture as the first texture to use in texture array
	m_currentTexture = 0;
	m_sprite->SetTexture(m_textures[m_currentTexture]);
	return true;
}

void SpriteAnimation::OnUpdate(float timestep)
{
	m_timeSinceLastTick += timestep;
	if (m_timeSinceLastTick >= this->GetUpdateInterval())
	{
		m_timeSinceLastTick = 0.0f;
		m_currentTexture = (m_currentTexture + 1) % m_textures.size();
		m_sprite->SetTexture(m_textures[m_currentTexture]);
	}
}

void SpriteAnimation::AddTexture(Texture* texture)
{
	m_textures.push_back(texture);
}
