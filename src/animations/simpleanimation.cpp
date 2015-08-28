#include "simpleanimation.hpp"
#include "../resourcemanager.hpp"
#include <iostream>

SimpleAnimation::SimpleAnimation(Json::Value animationJson,SpriteSceneNode* sprite)
: m_loop(animationJson["loop"].asBool())
, m_timePerFrame(animationJson["time"].asDouble())
, m_sprite(sprite)
, Animation()
{
    std::string path = animationJson["path"].asString();
    for (int i(0);i<animationJson["images"].size();i++)
    {
        addFrame(path+animationJson["images"][i].asString());
    }
}

void SimpleAnimation::start()
{
    m_curFrame=m_frames.begin();
    TextureManager* textures = TextureManager::instance();
    m_sprite->setTexture(textures->get(*m_curFrame));
    m_curTime=m_timePerFrame;
    m_sprite->setVisible(true);
    m_playing=true;
}

void SimpleAnimation::stop()
{
    m_sprite->setVisible(false);
    m_playing=false;
}

void SimpleAnimation::update(float dt)
{
    if(m_playing)
    {
        m_curTime-=dt;
        while (m_curTime<=0)
        {
            m_curTime+=m_timePerFrame;
            next();
        }
    }
}

void SimpleAnimation::next()
{
    m_curFrame++;
    if (m_curFrame == m_frames.end())
        m_curFrame = m_frames.begin();
    TextureManager* textures = TextureManager::instance();
    m_sprite->setTexture(textures->get(*m_curFrame));
}

void SimpleAnimation::addFrame(std::string imageName)
{
    std::cout << imageName << std::endl;
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

void SimpleAnimation::setSprite(SpriteSceneNode* sprite)
{
    m_sprite=sprite;
}
