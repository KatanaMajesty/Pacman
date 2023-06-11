#include <pch.h>

void Sprite::SetTexture(Texture* texture)
{
	sf::Texture& t = *reinterpret_cast<sf::Texture*>(texture->GetHandle());
	m_sprite.setTexture(t);
	m_texture = texture;
}

void Sprite::SetPosition(const Vec2& pos)
{
	m_sprite.setPosition(pos);
}

void Sprite::AddPosition(const Vec2& pos)
{
	m_sprite.move(pos);
}