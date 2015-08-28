#pragma once
#include "animation.hpp"
#include "../scenenode.hpp"
#include "../json/json.h"
#include <SFML/System/Vector2.hpp>

class ShakingAnimation : public Animation
{
    public:
        ShakingAnimation(Json::Value,SceneNode*);
        void update(float) override;
        void stop() override;
        void start() override;

    private:
        float getRandCoord();

    private:
        SceneNode* m_node;
        int m_amplitude;
        float m_soft;
        float m_curTime;
        float m_timePerShake;
        sf::Vector2f m_curPosition;
        sf::Vector2f m_curObjective;
};
