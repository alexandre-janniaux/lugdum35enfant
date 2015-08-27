#pragma once
#include "animationcomponent.hpp"
#include "animationgroup.hpp"
#include "animation.hpp"
#include "singleton.hpp"
#include "json/json.h"
#include <string>
#include <map>

class AnimationService : public Singleton<AnimationService>
{
    public:
        void open(int id,std::string fileName);

    private:
        std::unique_ptr<AnimationGroup> getGroupJson(Json::Value animationGroupJson,std::string path);
        std::unique_ptr<Animation> getAnimationJson(Json::Value animationJson, std::string path);

    private:
        std::map<int,AnimationComponent> m_animationComponents;
};
