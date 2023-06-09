#include "AudioManager.h"

#include <mutex>
#include "../Utility/FileSystem.h"
#include "../Utility/Logger.h"

std::mutex g_soundMutex;

static void SoundThread(std::queue<sf::Sound>* sounds, const bool* isDead)
{
    while (!(*isDead))
    {
        std::unique_lock lock(g_soundMutex);
        if (sounds->empty())
            continue;


        LOG("Status!");
        sounds->front().play();
        sounds->pop();
    }
}

AudioManager::AudioManager() 
{
    LoadSound(AUDIO_AMBIENCE, "ambience.wav");
    LoadSound(AUDIO_COIN_COLLECT, "coin_collect.wav");
    LoadSound(AUDIO_ENEMY_DEATH, "enemy_death.wav");
    LoadSound(AUDIO_FIGHT, "fight.wav");
    LoadSound(AUDIO_LEVEL_COMPLATED, "level_complated.wav");
    LoadSound(AUDIO_LEVEL_FAILED, "level_failed.wav");
    LoadSound(AUDIO_PLAYER_DEATH, "player_death.wav");
    m_soundThread = std::jthread(SoundThread, &m_sounds, &m_isDead);
}

AudioManager::~AudioManager()
{
    m_isDead = true;
}

AudioManager& AudioManager::Get()
{
    static AudioManager instance;
    return instance;
}

void AudioManager::LoadSound(AudioType audioType, const std::string& filename)
{
    static std::filesystem::path filepath = (FileSystem::Get().GetAssetsPath() / "Audio");
    std::string fullname = (filepath / filename).string();
    sf::SoundBuffer* buffer = new sf::SoundBuffer();
    if (!buffer->loadFromFile(fullname))
    {
        delete buffer;
        return;
    }
    m_soundBuffers[audioType] = std::unique_ptr<sf::SoundBuffer>(buffer);
}

void AudioManager::PlaySound(AudioType audioType)
{
    auto it = m_soundBuffers.find(audioType);
    if (it != m_soundBuffers.end()) 
    {
        sf::Sound sound(*it->second);
        sound.play();
        //std::unique_lock lock(g_soundMutex);
        //sf::Sound& sound = m_sounds.emplace(*it->second);
    }
}

//void AudioManager::StopSound(AudioType audioType) {
//    auto it = m_soundBuffers.find(audioType);
//    if (it != m_soundBuffers.end()) {
//        m_sound.setBuffer(it->second);
//        m_sound.stop();
//    }
//}