#pragma once
#include "animationgroup.hpp"
#include <string>
#include <memory>

class AnimationComponent
{
    public:
        void addGroup(std::string, std::unique_ptr<AnimationGroup>);

    private:
        std::map<std::string,std::unique_ptr<AnimationGroup>> m_animationGroups;
};
