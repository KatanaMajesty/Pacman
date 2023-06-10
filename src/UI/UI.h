#pragma once
#include <memory>

#include "../Core/Renderer.h"
#include "TextComponent.h"

struct LevelInfo
{
    uint32_t uCollectedCoins;
    uint32_t uOverallCoinsNumber;
    uint32_t uPlayerHealth;

    LevelInfo()
        : uCollectedCoins(0), uOverallCoinsNumber(0), uPlayerHealth(0) {}
    LevelInfo(uint32_t collectedCoins, uint32_t OverallCoinsNumber, uint32_t playerHealth)
        : uCollectedCoins(collectedCoins), uOverallCoinsNumber(OverallCoinsNumber), uPlayerHealth(playerHealth) {}
};

class UI
{
public:
    UI(Renderer* renderer);
    bool Init();
    void OnUpdate(float timestep);
    void SetLevelInfo(LevelInfo info) { m_levelInfo = info; }
private:
    Renderer* m_renderer;
    std::unique_ptr<Sprite> m_sprite;
    TextComponent* m_scoreText;
    TextComponent* m_healthText;
    TextComponent* m_youWonText;
    LevelInfo m_levelInfo;
};

