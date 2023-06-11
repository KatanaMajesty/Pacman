#include <pch.h>

bool SpriteAnimation::Init(float interval)
{
	ASSERT(interval > 0.001f);
	ASSERT(m_textures.size() > 0);
	m_interval = interval;
	m_timeSinceLastTick = 0.0f;
	m_currentTexture = 0;
	return true;
}

void SpriteAnimation::Apply(Sprite* sprite)
{
	ASSERT(sprite);
	sprite->SetTexture(m_textures[m_currentTexture]);
}

void SpriteAnimation::OnUpdate(float timestep)
{
	m_timeSinceLastTick += timestep;
	if (m_timeSinceLastTick >= this->GetUpdateInterval())
	{
		m_timeSinceLastTick = 0.0f;
		m_currentTexture = (m_currentTexture + 1) % m_textures.size();
	}
}

void SpriteAnimation::AddTexture(Texture* texture)
{
	m_textures.push_back(texture);
}
