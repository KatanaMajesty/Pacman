#include "Player.h"

#include "../Utility/Logger.h"

Player::Player()
{

}

void Player::OnUpdate(float timestep)
{
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
