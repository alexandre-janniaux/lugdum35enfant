#pragme once
#include <SFML/Audio.hpp>
#include <string>
#include "resourcemanager.hpp"

class SoundService
{
    public:
        void setVolume(float);
        float getVolume();

        void playSound(std::string& soundName);
        void loadMusics(std::string& lightMusicName,std::string& darkMusicName=std::string(""));
        void deleteFinished();
        void clearSounds();

        void playMusic(bool const& isLight=true);
        void pauseMusic();
        void stopMusic();

        void playSounds();
        void pauseSounds();
        void stopSounds();

    private:
        std::vector<sf::Sound> m_sounds;
        sf::Music* m_musicLight;
        sf::Music* m_musicDark;
        bool m_two;
        float m_volume;
};
