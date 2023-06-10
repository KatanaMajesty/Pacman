#include "Slimes.h"
#include <array>



//void FreezSlime::OnUpdate(float timestep){
//
//}

//void SlowSlime::OnUpdate(float timestep) {
//
//}

Slime::Slime(const Vec2& pos, const BoundingBox& boundingBox):Entity(pos, boundingBox){
	TextureAtlas& textureAtlas = TextureAtlas::Get();
	uint32_t textureWidth = textureAtlas.GetTextureWidth();
	uint32_t textureHeight = textureAtlas.GetTextureHeight();
	m_SlimePos = pos + Vec2(textureWidth / 2.0f, textureHeight / 2.0f);


	AnimationManager& animationManager = AnimationManager::Get();
	m_animation = AnimationManager::Get().CreateAnimation("slime_jump");
	m_animation->AddTexture(textureAtlas.GetTexture(TextureType::TEXTURE_SLIME_RED_IDLE));
	m_animation->AddTexture(textureAtlas.GetTexture(TextureType::TEXTURE_SLIME_RED_JUMPING));
	m_animation->Init(0.25f);
	m_sprite.SetPosition(m_pos);
	m_boundingBox = BoundingBox(m_SlimePos, 16.0f, 16.0f);

}

void Slime::OnUpdate(float timestep){
	AnimationManager::Get().Apply("slime_jump", &m_sprite);
	TextureAtlas& textureAtlas = TextureAtlas::Get();
	/*float w = textureAtlas.GetTextureWidth() / 2.0f;
	float h = textureAtlas.GetTextureHeight() / 2.0f;
	m_pos = m_pos + Vec2(w, h);
	this->SetAABB(m_pos, w);*/
	/*if (m_should_update_path == true) {
		UpdatePath(PlayerPos);
	}
	move();*/

}

void Slime::OnEntityCollision(Entity* entity) {

	if (entity->GetType() == ENTITY_PLAYER)
		AudioManager::Get().PlaySound(AudioType::AUDIO_PLAYER_DEATH);

};


//void FireSlime::move() {
//	if (m_path.empty())
//	{
//		m_should_update_path = true;
//		return;
//	}
//
//	m_pos = m_path.front();  //next point
//	m_path.erase(m_path.begin());
//
//	return;
//}

//void CoinSlime::OnUpdate(float timestep) {
//
//}
