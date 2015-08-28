#pragma once
#include <string>
#include <map>
#include <memory>
#include "animation.hpp"


class AnimationGroup
{
    public:
        void addAnimation(std::string,std::unique_ptr<Animation>);
        void update(float);
        void start();
        void stop();

    private:
        std::map<std::string,std::unique_ptr<Animation>> m_animations;
};
