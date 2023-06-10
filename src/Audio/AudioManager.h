#pragma once

#include <map>
#include <queue>
#include <thread>
#include <memory>
#include "../Utility/FileSystem.h"
#include <SFML/Audio.hpp>

enum AudioType // Changed to enum class for stronger typing
{
    AUDIO_AMBIENCE,
    AUDIO_COIN_COLLECT,
    AUDIO_ENEMY_DAMAGE,
    AUDIO_FIGHT,
    AUDIO_LEVEL_COMPLATED,
    AUDIO_LEVEL_FAILED,
    AUDIO_PLAYER_DEATH,
    AUDIO_DUBSTEP,
    NUM_AUDIOS
};

class AudioManager
{
public:
    AudioManager();
    ~AudioManager();

    static bool Init();
    static void Deinit();
    static AudioManager& Get();

    void PlaySound(AudioType audioType, float pitch = 1.0f, float volume = 20.0f);
    /*void StopSound(AudioType audioType);*/
    void LoadSound(AudioType audioType, const std::string& filename);

private:
    bool m_isDead = false;
    std::jthread m_soundThread;
    std::map<AudioType, sf::SoundBuffer> m_soundBuffers;
    std::queue<sf::Sound> m_sounds;

    static inline AudioManager* s_instance = nullptr;
};

