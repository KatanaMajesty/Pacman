#pragma once

#include "../Utility/FileSystem.h"
#include <SFML/Audio.hpp>
#include <map>

enum AudioType // Changed to enum class for stronger typing
{
    AUDIO_AMBIENCE,
    AUDIO_COIN_COLLECT,
    AUDIO_ENEMY_DEATH,
    AUDIO_FIGHT,
    AUDIO_LEVEL_COMPLATED,
    AUDIO_LEVEL_FAILED,
    AUDIO_PLAYER_DEATH,
    NUM_AUDIOS
};

class AudioManager
{
public:
    AudioManager();
    static AudioManager& Get();
    void PlaySound(AudioType audioType);
    void StopSound(AudioType audioType);
    void LoadSound(AudioType audioType, const std::string& filename);
private:
    std::map<AudioType, sf::SoundBuffer> m_soundBuffers;
    sf::Sound m_sound;
};

