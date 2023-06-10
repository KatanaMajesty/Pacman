#include "Slimes.h"
#include <array>



void FreezSlime::OnUpdate(float timestep){

}

void SlowSlime::OnUpdate(float timestep) {

}

FireSlime::FireSlime(const Vec2& pos, const BoundingBox& boundingBox, std::shared_ptr<Pathfinder>& pf):ISlime(pos, boundingBox, pf){
	TextureAtlas& textureAtlas = TextureAtlas::Get();
	uint32_t textureWidth = textureAtlas.GetTextureWidth();
	uint32_t textureHeight = textureAtlas.GetTextureHeight();
	m_SlimePos = pos + Vec2(textureWidth / 2.0f, textureHeight / 2.0f);
	m_sprites[0].SetTexture(textureAtlas.GetTexture(TextureType::TEXTURE_SLIME_RED_IDLE));
	m_sprites[1].SetTexture(textureAtlas.GetTexture(TextureType::TEXTURE_SLIME_RED_JUMPING));
}

void FireSlime::OnUpdate(float timestep, Vec2& PlayerPos){
	
	TextureAtlas& textureAtlas = TextureAtlas::Get();
	float w = textureAtlas.GetTextureWidth() / 2.0f;
	float h = textureAtlas.GetTextureHeight() / 2.0f;
	m_pos = m_pos + Vec2(w, h);
	this->SetAABB(m_pos, w);
	if (m_should_update_path == true) {
		UpdatePath(PlayerPos);
	}
	move();

}

void FireSlime::move() {
	if (m_path.empty())
	{
		m_should_update_path = true;
		return;
	}

	m_pos = m_path.front();  //next point
	m_path.erase(m_path.begin());

	return;
}

void CoinSlime::OnUpdate(float timestep) {

}
