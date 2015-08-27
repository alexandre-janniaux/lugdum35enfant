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

std::string AnimationGroup::getName()
{
    return m_name;
}
