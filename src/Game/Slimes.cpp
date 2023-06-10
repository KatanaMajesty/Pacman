#include "Slimes.h"

#include "AnimationManager.h"
#include "TextureAtlas.h"
#include "Player.h"

Slime::Slime(const Vec2& pos, const BoundingBox& boundingBox)
	: Entity(pos, boundingBox)
{
	TextureAtlas& textureAtlas = TextureAtlas::Get();
	uint32_t textureWidth = textureAtlas.GetTextureWidth();
	uint32_t textureHeight = textureAtlas.GetTextureHeight();
	m_SlimePos = pos + Vec2(textureWidth / 2.0f, textureHeight / 2.0f);


	AnimationManager& animationManager = AnimationManager::Get();
	m_animation = AnimationManager::Get().CreateAnimation("anim_slime");
	m_animation->AddTexture(textureAtlas.GetTexture(TextureType::TEXTURE_SLIME_RED_IDLE));
	m_animation->AddTexture(textureAtlas.GetTexture(TextureType::TEXTURE_SLIME_RED_JUMPING));
	m_animation->Init(0.25f);
	m_sprite.SetPosition(m_pos);
	m_boundingBox = BoundingBox(m_SlimePos, 16.0f, 16.0f);

}

void Slime::OnUpdate(float timestep)
{
	AnimationManager::Get().Apply("anim_slime", &m_sprite);
	m_timeSinceLastAttack += timestep;
}

void Slime::OnEntityCollision(Entity* entity) {

	if (entity->GetType() == ENTITY_PLAYER)
	{
		Player* player = (Player*)entity;
		if (m_timeSinceLastAttack > m_attackInterval)
		{
			AudioManager::Get().PlaySound(AudioType::AUDIO_ENEMY_DAMAGE);
			player->DealDamage();
			m_timeSinceLastAttack = 0.0f;
		}
	}
};