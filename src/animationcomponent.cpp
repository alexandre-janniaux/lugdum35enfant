#include "animationcomponent.hpp"

void AnimationComponent::addGroup(std::string name, std::unique_ptr<AnimationGroup> group)
{
    m_animationGroups.insert(std::pair<std::string,std::unique_ptr<AnimationGroup>>(name,std::move(group)));
}

void AnimationComponent::update(float dt)
{
    for (auto& it : m_animationGroups)
    {
        it.second->update(dt);
    }
}
