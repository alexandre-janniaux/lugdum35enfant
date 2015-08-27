#pragma once
#include <vector>
#include <string>
#include "spritescenenode.hpp"
#include "animation.hpp"

class SimpleAnimation : public Animation
{
    public:
        void update(float) override;
        void addFrame(std::string);
        void setFrameTime(float);
        void setLoop(bool);

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
