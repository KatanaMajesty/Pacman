#include "UI.h"

#include "TextManager.h"
#include "../Core/TextureLibrary.h"
#include "../Game/TextureAtlas.h"

UI::UI(Renderer* renderer)
    : m_renderer(renderer)
{
}

bool UI::Init()
{
    FileSystem& fs = FileSystem::Get();
    TextureLibrary& library = TextureLibrary::Get();
    std::string filepathTB = (fs.GetAssetsPath() / "textbox.png").string();

    m_sprite.reset(new Sprite);
    m_heartSprite.reset(new Sprite);

    Texture* textBoxTexture = library.CreateTexture(filepathTB);

    float vs = m_renderer->GetWindowViewsize();
    float scaleX = vs / textBoxTexture->GetWidth();
    float scaleY = vs / textBoxTexture->GetHeight();

    m_sprite.get()->SetTexture(textBoxTexture);
    m_sprite.get()->SetScale(scaleX, scaleY);

    TextManager& textManager = TextManager::Get();
    uint32_t fontsize = static_cast<uint32_t>(vs / 10.0f);
    m_scoreText = textManager.CreateText(fontsize, Vec2(0.025f * vs, static_cast<float>(fontsize)), TextFont::DEFAULT_FONT);
    m_scoreText->SetString("Score: {}", 0);
    m_scoreText->SetScale(0.6f, 1.2f);

    m_youWonText = textManager.CreateText(fontsize * 2, Vec2(0.025f * vs, static_cast<float>(2 * fontsize)), TextFont::DEFAULT_FONT);
    m_youWonText->SetString("You Won!", 0);
    m_youWonText->SetScale(0.6f, 1.2f);

    m_heartSprite.get()->SetTexture(TextureAtlas::Get().GetTexture(TextureType::TEXTURE_HEART));
    m_heartSprite.get()->SetPosition(Vec2(0.025f * vs, static_cast<float>(3 * fontsize)));
    m_heartSprite.get()->SetScale(scaleX / 4.0f, scaleY / 4.0f);

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

    Sprite heart = *m_heartSprite.get();
    for (uint32_t i = 0; i < m_levelInfo.uPlayerHealth; i++)
    {
        const Vec2& firstHeartPosition = m_heartSprite.get()->GetPosition();
        heart.SetPosition(Vec2(firstHeartPosition.x + 1.5f * i * m_heartSprite.get()->GetTexture()->GetWidth(), firstHeartPosition.y));
        m_renderer->Draw(&heart);
    }
}
