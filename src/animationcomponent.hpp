#pragma once
#include "animationgroup.hpp"
#include <string>
#include <memory>

class AnimationComponent
{
    public:
        void addGroup(std::string, std::unique_ptr<AnimationGroup>);
        void update(float);
        void play(std::string);
        void stop();

    private:
        std::map<std::string,std::unique_ptr<AnimationGroup>> m_animationGroups;
        std::string m_currentAnimation;
};
