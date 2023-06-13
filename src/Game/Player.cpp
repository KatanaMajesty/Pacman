#include "pch.h"
#include "Player.h"

Player::Player(const Vec2& pos, const BoundingBox& boundingBox)
	: Entity(pos, boundingBox)
{
	TextureAtlas& textureAtlas = TextureAtlas::Get();
	uint32_t textureWidth = textureAtlas.GetTextureWidth();
	uint32_t textureHeight = textureAtlas.GetTextureHeight();
	m_playerPos = pos + Vec2(textureWidth / 2.0f, textureHeight / 2.0f);

	m_sprites[static_cast<unsigned int>(Direction::DIRECTION_UP)].SetTexture(textureAtlas.GetTexture(TextureType::TEXTURE_PLAYER_BACK));
	m_sprites[static_cast<unsigned int>(Direction::DIRECTION_LEFT)].SetTexture(textureAtlas.GetTexture(TextureType::TEXTURE_PLAYER_LEFT));
	m_sprites[static_cast<unsigned int>(Direction::DIRECTION_DOWN)].SetTexture(textureAtlas.GetTexture(TextureType::TEXTURE_PLAYER_FRONT));
	m_sprites[static_cast<unsigned int>(Direction::DIRECTION_RIGHT)].SetTexture(textureAtlas.GetTexture(TextureType::TEXTURE_PLAYER_RIGHT));

	m_damageSprites[static_cast<unsigned int>(Direction::DIRECTION_UP)].SetTexture(textureAtlas.GetTexture(TextureType::TEXTURE_PLAYER_IMMUNE_BACK));
	m_damageSprites[static_cast<unsigned int>(Direction::DIRECTION_LEFT)].SetTexture(textureAtlas.GetTexture(TextureType::TEXTURE_PLAYER_IMMUNE_LEFT));
	m_damageSprites[static_cast<unsigned int>(Direction::DIRECTION_DOWN)].SetTexture(textureAtlas.GetTexture(TextureType::TEXTURE_PLAYER_IMMUNE_FRONT));
	m_damageSprites[static_cast<unsigned int>(Direction::DIRECTION_RIGHT)].SetTexture(textureAtlas.GetTexture(TextureType::TEXTURE_PLAYER_IMMUNE_RIGHT));
	
	SetDirection(Direction::DIRECTION_DOWN);
	m_activeSprite = &m_sprites[static_cast<unsigned int>(Direction::DIRECTION_DOWN)];
}

void Player::OnUpdate(float timestep)
{
	m_lastTimestep = timestep;

	if (!m_activeSprite)
		return;

	TextureAtlas& textureAtlas = TextureAtlas::Get();
	float w = textureAtlas.GetTextureWidth() / 2.0f;
	float h = textureAtlas.GetTextureHeight() / 2.0f;
	m_playerPos = m_pos + Vec2(w, h);

	this->SetAABB(m_playerPos, w);
	this->CanMove() = true;

	// Hardcoded 4 seconds of damage resistance
	m_timeSinceDamageDealt += timestep;
	if (m_timeSinceDamageDealt > 4.0f)
		m_activeSprite = &m_sprites[static_cast<unsigned int>(m_direction)];
	else
		m_activeSprite = &m_damageSprites[static_cast<unsigned int>(m_direction)];
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
	case EntityType::ENTITY_TILE: this->OnTileCollision(); break;
	case EntityType::ENTITY_PLAYER: // should not happen
	case EntityType::ENTITY_UNKNOWN:
	default: ASSERT(false); break;
	}
}

void Player::OnCoinPickup()
{
	++m_collectedCoins;
}

void Player::OnWeaponPickup()
{
}

void Player::OnEnemyInteract()
{
	if (!IsImmune())
		m_timeSinceDamageDealt = 0.0f;
}

void Player::OnTileCollision()
{
	Vec2 oppositeDirection = VecFromDirection(GetOppositeDirection(m_collisionDirection));
	float pixels= 32.0f * m_lastTimestep; // how many pixels to offset per second
	AddPosition(oppositeDirection * pixels); // use timestep to avoid relying on FPS
}