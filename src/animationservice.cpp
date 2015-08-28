#include "animationservice.hpp"
#include <fstream>
#include <iostream>
#include "animations/simpleanimation.hpp"

SceneNode* AnimationService::m_rootNode=nullptr;

void AnimationService::setRootNode(SceneNode& sceneNode)
{
    m_rootNode=&sceneNode;
}

void AnimationService::open(int id,std::string fileName)
{
    AnimationComponent component;

    std::ifstream file(fileName.c_str());
    if (!file)
    {
        std::cout << "Error: can't open file " << fileName << std::endl;
        return;
    }

    Json::Value root;
    Json::Reader reader;
    if( !reader.parse(file, root, false) )
    {
        std::cout << "Error while reading animation file:\n" << reader.getFormattedErrorMessages();
        return;
    }
    Json::Value _animations=root["animations"];
    for (int i(0);i<_animations.size();i++)
    {
        component.addGroup(_animations[i]["name"].asString(),getGroupJson(_animations[i]["content"]));
    }
    m_animationComponents.emplace(id,std::move(component));
}

std::unique_ptr<AnimationGroup> AnimationService::getGroupJson(Json::Value animationGroupJson)
{
    std::unique_ptr<AnimationGroup> _animationGroup (new AnimationGroup);
    for (int i(0);i<animationGroupJson.size();i++)
    {
        _animationGroup->addAnimation(animationGroupJson[i]["name"].asString(),getAnimationJson(animationGroupJson[i]));
    }
    return std::move(_animationGroup);
}

std::unique_ptr<Animation> AnimationService::getAnimationJson(Json::Value animationJson)
{
    std::string _type=animationJson["type"].asString();
    if(_type=="simple")
    {
        std::unique_ptr<SimpleAnimation> animation (new SimpleAnimation(animationJson,findSpriteSceneNode(animationJson["node"].asInt())));
        return std::move(animation);
    }
}

void AnimationService::update(float dt)
{
    for (auto& it : m_animationComponents)
    {
        it.second.update(dt);
    }
}

SpriteSceneNode* AnimationService::findSpriteSceneNode(int value)
{
    if (value==1)
    {
        SpriteSceneNode* sprite (new SpriteSceneNode(0));
        sprite->attachParent(*m_rootNode);
        return sprite;
    }
}

void AnimationService::play(int id,std::string animationName)
{
    auto it = m_animationComponents.find(id);
    if(it==m_animationComponents.end())
    {
        std::cout << "Error : Couldn't play animation (No animation loaded)" << std::endl;
        return;
    }
    it->second.play(animationName);
}
