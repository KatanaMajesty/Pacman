#include "AudioManager.h"

#include <mutex>
#include "../Utility/FileSystem.h"
#include "../Utility/Logger.h"

std::mutex g_soundMutex;

static void SoundThread(std::queue<sf::Sound>* sounds, const bool* isDead)
{
    while (!(*isDead))
    {
        std::lock_guard lock(g_soundMutex);
        if (sounds->empty())
            continue;

        sf::Sound& queried = sounds->front();
        if (queried.getStatus() == sf::SoundSource::Playing)
            continue;

        sounds->pop();
    }
}

AudioManager::AudioManager() 
{
    m_soundThread = std::jthread(SoundThread, &m_sounds, &m_isDead);
}

AudioManager::~AudioManager()
{
    m_isDead = true;
}

bool AudioManager::Init()
{
    if (s_instance)
        Deinit();

    s_instance = new AudioManager();
    s_instance->LoadSound(AUDIO_AMBIENCE, "ambience.wav");
    s_instance->LoadSound(AUDIO_COIN_COLLECT, "coin_collect.wav");
    s_instance->LoadSound(AUDIO_ENEMY_DEATH, "enemy_death.wav");
    s_instance->LoadSound(AUDIO_FIGHT, "fight.wav");
    s_instance->LoadSound(AUDIO_LEVEL_COMPLATED, "level_complated.wav");
    s_instance->LoadSound(AUDIO_LEVEL_FAILED, "level_failed.wav");
    s_instance->LoadSound(AUDIO_PLAYER_DEATH, "player_death.wav");
    s_instance->LoadSound(AUDIO_DUBSTEP, "far_cry_dubstep.wav");
    return true;
}

void AudioManager::Deinit()
{
    if (s_instance)
    {
        delete s_instance;
        s_instance = nullptr;
    }
}

AudioManager& AudioManager::Get()
{
    return *s_instance;
}

void AudioManager::LoadSound(AudioType audioType, const std::string& filename)
{
    static std::filesystem::path filepath = (FileSystem::Get().GetAssetsPath() / "Audio");
    sf::SoundBuffer buffer;
    if (buffer.loadFromFile((filepath / filename).string())) {
        m_soundBuffers[audioType] = buffer;
    }
}

void AudioManager::PlaySound(AudioType audioType, float pitch, float volume)
{
    auto it = m_soundBuffers.find(audioType);
    if (it != m_soundBuffers.end()) 
    {
        std::lock_guard lock(g_soundMutex);
        sf::Sound& sound = m_sounds.emplace(it->second);
        sound.setVolume(volume);
        sound.setPitch(pitch);
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