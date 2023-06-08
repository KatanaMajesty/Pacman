#include "Player.h"

#include "../Utility/Logger.h"
#include "TextureAtlas.h"

Player::Player()
{
	TextureAtlas& textureAtlas = TextureAtlas::Get();
	m_sprites[DIRECTION_UP].SetTexture(textureAtlas.GetTexture(TextureType::TEXTURE_PLAYER_BACK));
	m_sprites[DIRECTION_LEFT].SetTexture(textureAtlas.GetTexture(TextureType::TEXTURE_PLAYER_LEFT));
	m_sprites[DIRECTION_DOWN].SetTexture(textureAtlas.GetTexture(TextureType::TEXTURE_PLAYER_FRONT));
	m_sprites[DIRECTION_RIGHT].SetTexture(textureAtlas.GetTexture(TextureType::TEXTURE_PLAYER_RIGHT));
}

void Player::OnUpdate(float timestep)
{
	for (uint32_t i = 0; i < 4; ++i)
		m_sprites[i].SetPosition(m_position);
}

void Player::OnEntityCollision(Entity* entity)
{
	EntityType otherType = entity->GetType();
	switch (otherType)
	{
	case EntityType::ENTITY_COIN: this->OnCoinPickup(); break;
	case EntityType::ENTITY_WEAPON: this->OnWeaponPickup(); break;
	case EntityType::ENTITY_ENEMY: this->OnEnemyInteract(); break;
	case EntityType::ENTITY_PLAYER: // should not happen
	case EntityType::ENTITY_UNKNOWN:
	default: ASSERT(false); break;
	}
}

void Player::OnCoinPickup()
{
}

void Player::OnWeaponPickup()
{
}

void Player::OnEnemyInteract()
{
}
