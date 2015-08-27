#include "simpleanimation.hpp"
#include "resourcemanager.hpp"

void SimpleAnimation::update(float dt)
{
    m_curTime-=dt;
    while (m_curTime<=0)
    {
        m_curTime+=m_timePerFrame;
        next();
    }
}

void SimpleAnimation::next()
{
    m_curFrame++;
    if (m_curFrame == m_frames.end())
        m_curFrame == m_frames.begin();
    TextureManager* textures = TextureManager::instance();
    m_sprite->setTexture(textures->get(*m_curFrame));
}

void SimpleAnimation::addFrame(std::string imageName)
{
    m_frames.push_back(imageName);
}

void SimpleAnimation::setFrameTime(float time)
{
    m_timePerFrame=time;
}

void SimpleAnimation::setLoop(bool loop)
{
    m_loop=loop;
}
