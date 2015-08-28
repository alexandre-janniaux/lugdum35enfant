#include "shakinganimation.hpp"
#include <cmath>
#include <iostream>

ShakingAnimation::ShakingAnimation(Json::Value animationJson,SceneNode* node)
: m_amplitude(animationJson["amplitude"].asInt())
, m_soft(animationJson["soft"].asDouble())
, m_timePerShake(animationJson["time"].asDouble())
, m_node(node)
, Animation()
{

}

void ShakingAnimation::start()
{
    m_curObjective=sf::Vector2f(getRandCoord(),getRandCoord());
    m_curTime=m_timePerShake;
    m_playing=true;
}

void ShakingAnimation::stop()
{
    m_curObjective=sf::Vector2f(0.f,0.f);
    m_playing=false;
}


void ShakingAnimation::update(float dt)
{
    if(m_playing)
    {
        m_curTime-=dt;
        while (m_curTime<=0)
        {
            m_curTime+=m_timePerShake;
            m_curObjective=sf::Vector2f(getRandCoord(),getRandCoord());
        }
    }
    sf::Vector2f _calculatedPosition=m_curPosition*m_soft+m_curObjective*(1.f-m_soft);
    m_node->setPosition(_calculatedPosition-m_curPosition+m_node->getPosition());
    m_curPosition=_calculatedPosition;
}

float ShakingAnimation::getRandCoord()
{
    return ((float)(rand()%m_amplitude)-((float)m_amplitude)/2.f);
}
