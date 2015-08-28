#pragma once
#include "animations/animationcomponent.hpp"
#include "animations/animationgroup.hpp"
#include "animations/animation.hpp"
#include "singleton.hpp"
#include "json/json.h"
#include <string>
#include <map>

class AnimationService : public Singleton<AnimationService>
{
    public:
        void open(int id,std::string fileName);
        void play(int id,std::string animationName);
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
