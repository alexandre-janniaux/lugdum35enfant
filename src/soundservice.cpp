#include "soundservice.hpp"

void SoundService::playSound(std::string& soundName)
{
    auto buffers = BufferManager::instance();
    sf::SoundBuffer& _buffer = buffers->get(soundName);
    m_sounds.push_back(make_unique<sf::Sound>(_buffer));
    m_sounds.back()->play();
}

void SoundService::loadMusics(std::string& lightMusicName,std::string& darkMusicName)
{
    auto musics = MusicManager::instance();
    sf::Music& _lightMusic = musics->get(lightMusicName);
    m_lightMusic = &_lightMusic;
    m_lightMusic->setLoop(true);

    if (!darkMusicName.empty())
    {
        sf::Music& _darkMusic = musics->get(darkMusicName);
        m_darkMusic = &_lightMusic;
        m_darkMusic->setLoop(true);
        m_two=true;
    }
    else
    {
        if (m_two)
            m_darkMusic.stop();
        m_two=false;
    }
    playMusic(true);
}

void SoundService::setVolume(float volume)
{
    m_volume=volume;
}

float SoundService::getVolume()
{
    return m_volume;
}

void SoundService::playMusic(bool const& isLight)
{
    if (m_two)
    {
        m_lightMusic->play();
        m_darkMusic->play();
        if (isLight)
        {
            m_lightMusic->setVolume(m_volume);
            m_darkMusic->setVolume(0.f);
        }
        else
        {
            m_lightMusic->setVolume(0.f);
            m_darkMusic->setVolume(m_volume);
        }
    }
    else
    {
        m_lightMusic->play();
        m_lightMusic->setVolume(m_volume);
    }
}

void SoundService::pauseMusic();
{
    m_lightMusic->pause();
    if (m_two)
        m_darkMusic->pause();
}

void SoundService::stopMusic();
{
    m_lightMusic->stop();
    if (m_two)
        m_darkMusic->stop();
}

void SoundService::deleteFinished()
{
    for (auto& it : m_sounds)
    {
        if (it->getStatus()==sf::SoundSource::Stopped)
            m_sounds.erase(it);
    }
}

void SoundService::playSounds()
{
    for (auto& it : m_sounds)
    {
        m_sounds->play();
    }
}

void SoundService::pauseSounds()
{
    for (auto& it : m_sounds)
    {
        m_sounds->pause();
    }
}

void SoundService::stopSounds()
{
    for (auto& it : m_sounds)
    {
        m_sounds->stop();
    }
}

void SoundService::clearSounds()
{
    for (auto& it : m_sounds)
    {
        m_sounds.erase(it);
    }
}
