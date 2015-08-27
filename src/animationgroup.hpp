#pragma once
#include <string>
#include <map>
#include <memory>
#include "animation.hpp"


class AnimationGroup
{
    public:
        void addAnimation(std::string,std::unique_ptr<Animation>);
        std::string getName();
        void update(float);


    private:
        std::string m_name;
        std::map<std::string,std::unique_ptr<Animation>> m_animations;
};
