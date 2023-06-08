#pragma once
#include "../Utility/FileSystem.h"
#include <SFML/Audio.hpp>
enum AudioType // Changed to enum class for stronger typing
{
    
};

class AudioManager
{
private:
    sf::SoundBuffer buffer;
public:
    AudioManager() = default;
    void PlaySound(AudioType audioType);
    void LoadSound(AudioType audioType, const std::string& filename);
};