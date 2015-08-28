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
        void setRootNode(SceneNode&);
        void update(float);

    private:
        SpriteSceneNode* findSpriteSceneNode(int);
        std::unique_ptr<AnimationGroup> getGroupJson(Json::Value animationGroupJson);
        std::unique_ptr<Animation> getAnimationJson(Json::Value animationJson);

    private:
        std::map<int,AnimationComponent> m_animationComponents;
        static SceneNode* m_rootNode;
};
