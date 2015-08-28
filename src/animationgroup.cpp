#include "animationgroup.hpp"

void AnimationGroup::addAnimation(std::string name,std::unique_ptr<Animation> animation)
{
    m_animations.emplace(name,std::move(animation));
}

void AnimationGroup::update(float dt)
{
    for(auto& animation : m_animations)
    {
        animation.second->update(dt);
    }
}

void AnimationGroup::start()
{
    for(auto& animation : m_animations)
    {
        animation.second->start();
    }
}

void AnimationGroup::stop()
{
    for(auto& animation : m_animations)
    {
        animation.second->stop();
    }
}
