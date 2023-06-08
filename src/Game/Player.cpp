#include "Player.h"

#include "../Utility/Logger.h"
#include "TextureAtlas.h"

Player::Player(const Vec2& pos, const BoundingBox& boundingBox)
	: Entity(pos, boundingBox)
{
	TextureAtlas& textureAtlas = TextureAtlas::Get();
	m_sprites[DIRECTION_UP].SetTexture(textureAtlas.GetTexture(TextureType::TEXTURE_PLAYER_BACK));
	m_sprites[DIRECTION_LEFT].SetTexture(textureAtlas.GetTexture(TextureType::TEXTURE_PLAYER_LEFT));
	m_sprites[DIRECTION_DOWN].SetTexture(textureAtlas.GetTexture(TextureType::TEXTURE_PLAYER_FRONT));
	m_sprites[DIRECTION_RIGHT].SetTexture(textureAtlas.GetTexture(TextureType::TEXTURE_PLAYER_RIGHT));
	this->SetDirection(DIRECTION_DOWN);
}

void Player::OnUpdate(float timestep)
{
	if (!m_activeSprite)
		return;

	m_activeSprite->SetPosition(m_pos);

	// Do player logic
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

void Player::SetDirection(Direction direction)
{
	m_activeSprite = &m_sprites[direction];
}
