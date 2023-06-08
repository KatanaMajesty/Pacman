#pragma once

#include "../Core/Texture.h"
#include "../Utility/Math.h"

class Sprite
{
public:
	Sprite() = default;

	void SetTexture(Texture* texture);
	void SetPosition(const Vec2& pos);
	void AddPosition(const Vec2& pos);
	void SetScale(float scale) { m_sprite.scale(scale, scale); }
	void SetScale(const Vec2& scale) { m_sprite.scale(scale); }
	void SetRotation(float angle) { m_sprite.setRotation(angle); }
	inline Texture* GetTexture() { return m_texture; }
	inline const Vec2& GetPosition() const { return m_sprite.getPosition(); }

protected:
	friend class Renderer;

	sf::Sprite m_sprite;
	Texture* m_texture = nullptr;
};