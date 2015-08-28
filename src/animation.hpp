#pragma once
#include "spritescenenode.hpp"

class Animation
{
    public:
        virtual void update(float){};
        virtual void stop();
        virtual void start();

    protected:
        bool m_playing;
};
