#include "Coin.h"

#include "TextureAtlas.h"

Coin::Coin(const Vec2& pos, const BoundingBox& boundingBox)
	: Entity(pos, boundingBox)
{
	TextureAtlas& atlas = TextureAtlas::Get();
	m_sprite.SetTexture(atlas.GetTexture(TEXTURE_COIN));
	m_sprite.SetPosition(m_pos);
	SetAABB(32.0f, 32.0f);
}

void Coin::OnUpdate(float timestep)
{
	
}

void Coin::OnEntityCollision(Entity* entity)
{
}
