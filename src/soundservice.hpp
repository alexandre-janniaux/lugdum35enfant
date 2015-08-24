#pragma once
#include <SFML/Audio.hpp>
#include <string>
#include "resourcemanager.hpp"
#include "singleton.hpp"

class SoundService : public Singleton<SoundService>
{
    public:
        void setVolume(float);
        float getVolume();

        void playSound(std::string& soundName);
        void loadMusics(const std::string& lightMusicName,const std::string& darkMusicName=std::string(""));
        void update();
        void clearSounds();

        void playMusic(bool const& isLight=true);
        void pauseMusic();
        void stopMusic();

        void playSounds();
        void pauseSounds();
        void stopSounds();

    private:
        std::vector<std::unique_ptr<sf::Sound>> m_sounds;
        sf::Music* m_lightMusic;
        sf::Music* m_darkMusic;
        bool m_two=false;
        float m_volume;
};
