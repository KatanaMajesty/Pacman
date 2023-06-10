#pragma once
#include <memory>

#include "../Core/Renderer.h"
#include "../Game/Coin.h"
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
    std::unique_ptr<Sprite> m_heartSprite;
    //std::unique_ptr<Sprite> m_coinSprite;
    std::unique_ptr<Coin> m_coin;
    TextComponent* m_youWonText;
    TextComponent* m_gameOverText;
    LevelInfo m_levelInfo;
};

