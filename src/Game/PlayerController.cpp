#include "pch.h"

#include "PlayerController.h"

PlayerController::PlayerController(Player* player)
    : m_player(player)
{
}

void PlayerController::OnMoveUp(float timestep)
{
    m_player->SetDirection(Direction::DIRECTION_UP);
    Vec2 offset(0.0f, -timestep * m_speed);
    m_player->AddPosition(offset);
}

void PlayerController::OnMoveDown(float timestep)
{
    m_player->SetDirection(Direction::DIRECTION_DOWN);
    Vec2 offset(0.0f, timestep * m_speed);
    m_player->AddPosition(offset);
}

void PlayerController::OnMoveLeft(float timestep)
{
    m_player->SetDirection(Direction::DIRECTION_LEFT);
    Vec2 offset(-timestep * m_speed, 0.0f);
    m_player->AddPosition(offset);
}

void PlayerController::OnMoveRight(float timestep)
{
    m_player->SetDirection(Direction::DIRECTION_RIGHT);
    Vec2 offset(timestep * m_speed, 0.0f);
    m_player->AddPosition(offset);
}