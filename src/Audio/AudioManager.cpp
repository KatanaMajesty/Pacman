#include "AudioManager.h"
#include "../Utility/FileSystem.h"

AudioManager::AudioManager() 
{
    LoadSound(AUDIO_AMBIENCE, "ambience.wav");
    LoadSound(AUDIO_COIN_COLLECT, "coin_collect.wav");
    LoadSound(AUDIO_ENEMY_DEATH, "enemy_death.wav");
    LoadSound(AUDIO_FIGHT, "fight.wav");
    LoadSound(AUDIO_LEVEL_COMPLATED, "level_complated.wav");
    LoadSound(AUDIO_LEVEL_FAILED, "level_failed.wav");
    LoadSound(AUDIO_PLAYER_DEATH, "player_death.wav");
}

AudioManager& AudioManager::Get()
{
    static AudioManager instance;
    return instance;
}

void AudioManager::LoadSound(AudioType audioType, const std::string& filename)
{
    static std::filesystem::path filepath = (FileSystem::Get().GetAssetsPath() / "Audio");
    sf::SoundBuffer buffer;
    if (buffer.loadFromFile((filepath / filename).string())) {
        m_soundBuffers[audioType] = buffer;
    }
}

void AudioManager::PlaySound(AudioType audioType)
{
    auto it = m_soundBuffers.find(audioType);
    if (it != m_soundBuffers.end()) {
        sf::Sound& sound = m_sounds.emplace();
        sound.setBuffer(it->second);
        sound.play();
    }
}

//void AudioManager::StopSound(AudioType audioType) {
//    auto it = m_soundBuffers.find(audioType);
//    if (it != m_soundBuffers.end()) {
//        m_sound.setBuffer(it->second);
//        m_sound.stop();
//    }
//}