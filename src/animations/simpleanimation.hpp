#pragma once
#include <vector>
#include <string>
#include "../spritescenenode.hpp"
#include "animation.hpp"
#include "../json/json.h"

class SimpleAnimation : public Animation
{
    public:
        SimpleAnimation(Json::Value,SpriteSceneNode* sprite=nullptr);
        void addFrame(std::string);
        void setFrameTime(float);
        void setLoop(bool);
        void setSprite(SpriteSceneNode*);

        void update(float) override;
        void start() override;
        void stop() override;

    private:
        void next();

    private:
        SpriteSceneNode* m_sprite;
        std::vector<std::string> m_frames;
        std::vector<std::string>::iterator m_curFrame;
        float m_timePerFrame;
        float m_curTime;
        bool m_loop;
};
