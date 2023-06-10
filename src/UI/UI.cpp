#include "UI.h"

#include "TextManager.h"
#include "../Core/TextureLibrary.h"

UI::UI(Renderer* renderer)
    : m_renderer(renderer)
{
}

bool UI::Init()
{
    FileSystem& fs = FileSystem::Get();
    TextureLibrary& library = TextureLibrary::Get();
    std::string filepath = (fs.GetAssetsPath() / "textbox.png").string();

    m_sprite.reset(new Sprite);

    Texture* t = library.CreateTexture(filepath);
    float vs = m_renderer->GetWindowViewsize();
    float scaleX = vs / t->GetWidth();
    float scaleY = vs / t->GetHeight();
    m_sprite.get()->SetTexture(t);
    m_sprite.get()->SetScale(scaleX, scaleY);

    TextManager& textManager = TextManager::Get();
    uint32_t fontsize = static_cast<uint32_t>(vs / 10.0f);
    m_scoreText = textManager.CreateText(fontsize, Vec2(0.025f * vs, 0.1f * vs), TextFont::DEFAULT_FONT);
    m_scoreText->SetString("Score: {}", 0);
    m_scoreText->SetScale(0.6f, 1.2f);

    m_healthText = textManager.CreateText(fontsize, Vec2(0.025f * vs, 3 * 0.1f * vs), TextFont::DEFAULT_FONT);
    m_healthText->SetString("Health: {}", 0);
    m_healthText->SetScale(0.6f, 1.2f);

    m_youWonText = textManager.CreateText(fontsize * 2, Vec2(0.025f * vs, 0.1f * vs), TextFont::DEFAULT_FONT);
    m_youWonText->SetString("You Won!", 0);
    m_youWonText->SetScale(0.6f, 1.2f);

    return true;
}

void UI::OnUpdate(float timestep)
{
    m_renderer->Draw(m_sprite.get());

    if (m_levelInfo.uCollectedCoins == m_levelInfo.uOverallCoinsNumber)
    {
        m_renderer->Draw(m_youWonText);
        return;
    }
    else if(m_levelInfo.uPlayerHealth == 0){
        //m_renderer->Draw(m_youWonText);
        return;
    }

    m_scoreText->SetString("Score: {}", m_levelInfo.uCollectedCoins);
    m_renderer->Draw(m_scoreText);

    m_healthText->SetString("Health: {}", m_levelInfo.uPlayerHealth);
    m_renderer->Draw(m_healthText);
}
