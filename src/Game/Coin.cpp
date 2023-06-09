#include "Coin.h"

#include "../Audio/AudioManager.h"
#include "TextureAtlas.h"

Coin::Coin(const Vec2& pos, const BoundingBox& boundingBox)
	: Entity(pos, boundingBox)
{
	TextureAtlas& atlas = TextureAtlas::Get();
	m_sprite.SetTexture(atlas.GetTexture(TEXTURE_COIN));
	m_sprite.SetPosition(m_pos);
	m_boundingBox = BoundingBox(pos, 32.0f, 32.0f);
}

void Coin::OnUpdate(float timestep)
{
	
}

void Coin::OnEntityCollision(Entity* entity)
{
	if (entity->GetType() == ENTITY_PLAYER)
		AudioManager::Get().PlaySound(AudioType::AUDIO_COIN_COLLECT);
}
