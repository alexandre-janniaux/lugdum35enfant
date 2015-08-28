#include "animationservice.hpp"
#include <fstream>
#include <iostream>
#include "animations/simpleanimation.hpp"
#include "animations/shakinganimation.hpp"

SceneNode* AnimationService::m_rootNode=nullptr;

void AnimationService::setRootNode(SceneNode& sceneNode)
{
    m_rootNode=&sceneNode;
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
    else if(_type=="shake")
    {
        std::unique_ptr<ShakingAnimation> animation (new ShakingAnimation(animationJson,findSceneNode(animationJson["node"].asInt())));
        return std::move(animation);
    }
    else
    {
        std::cout << "Error : Animation type not known." << std::endl;
        return std::move(std::unique_ptr<Animation>());
    }
}

void AnimationService::update(float dt)
{
    for (auto& it : m_animationComponents)
    {
        it.second.update(dt);
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

void AnimationService::open(int id,std::string fileName)
{
    AnimationComponent component;
    m_nodeMap.clear();
    m_spriteNodeMap.clear();
    m_nodeMap.emplace(0,m_rootNode);

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
    makeNodeMap(root["nodes"]);
    Json::Value _animations=root["animations"];
    for (int i(0);i<_animations.size();i++)
    {
        component.addGroup(_animations[i]["name"].asString(),getGroupJson(_animations[i]["content"]));
    }
    m_animationComponents.emplace(id,std::move(component));

    m_nodeMap.clear();
    m_spriteNodeMap.clear();
}

//Awful, has to change :

void AnimationService::makeNodeMap(Json::Value nodes)
{
    for(int i(0) ; i<nodes.size() ; i++)
    {
        Json::Value node=nodes[i];
        if(node["create"].asBool())
        {
            SceneNode* _sceneNode=findSceneNode(node["from"].asInt());
            if(node["sprite"].asBool())
            {
                SpriteSceneNode* _result (new SpriteSceneNode(node.get("layer",0).asInt()));
                _result->attachParent(*_sceneNode);
                m_spriteNodeMap.emplace(node["name"].asInt(),_result);
            }
            else
            {
                SceneNode* _result (new SceneNode(node.get("layer",0).asInt()));
                _result->attachParent(*_sceneNode);
                m_nodeMap.emplace(node["name"].asInt(),_result);
            }
        }
        else
        {
            //TODO
        }
    }
}

SceneNode* AnimationService::findSceneNode(int value)
{
    auto it=m_nodeMap.find(value);
    if (it!=m_nodeMap.end())
    {
        return m_nodeMap[value];
    };
    return m_spriteNodeMap[value];
}

SpriteSceneNode* AnimationService::findSpriteSceneNode(int value)
{
    return m_spriteNodeMap[value];
}
