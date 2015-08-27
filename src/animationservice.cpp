#include "animationservice.hpp"
#include <fstream>
#include <iostream>
#include "simpleanimation.hpp"

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
    std::string _path=root["path"].asString();
    Json::Value _animations=root["animations"];
    for (int i(0);i<_animations.size();i++)
    {
        component.addGroup(_animations[i]["name"].asString(),getGroupJson(_animations[i]["content"],_path));
    }
    m_animationComponents.emplace(id,std::move(component));
}

std::unique_ptr<AnimationGroup> AnimationService::getGroupJson(Json::Value animationGroupJson,std::string path)
{
    std::unique_ptr<AnimationGroup> _animationGroup (new AnimationGroup);
    //std::string _path=animationGroupJson["path"]
    for (int i(0);i<animationGroupJson.size();i++)
    {
        _animationGroup->addAnimation(animationGroupJson[i]["name"].asString(),getAnimationJson(animationGroupJson[i],path));
    }
    return std::move(_animationGroup);
}

std::unique_ptr<Animation> AnimationService::getAnimationJson(Json::Value animationJson, std::string path)
{
    std::string _type=animationJson["type"].asString();
    if(_type=="simple")
    {
        std::unique_ptr<SimpleAnimation> animation (new SimpleAnimation);
        for (int i(0);i<animationJson["images"].size();i++)
        {
            animation->addFrame(path+animationJson["images"][i].asString());
        }
        animation->setFrameTime(animationJson["time"].asDouble());
        animation->setLoop(animationJson["loop"].asBool());
        return std::move(animation);
    }
}
