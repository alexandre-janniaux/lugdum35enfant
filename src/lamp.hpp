#pragma once
#include <SFML/Graphics.hpp>
#include "scenenode.hpp"
#include "geometry.cpp"
#include <cmath>

namespace Math
{
    const float PI=3.14159265358979f;
}

class Lamp : public SceneNode
{
    public:
        void computeLight(std::vector<sf::Rect<float>> const&);
        void addRay(sf::Vector2f, sf::Vector2f);

    private:
        void generateBaseRay();
        void createRay(float, float);
        std::vector<segment> splitRay(segment,segment);
        std::vector<segment> rectangleToSegments(sf::Rect<float> const&);
        void buildRays();

    private:
        bool m_computedLight;
        //static float distance(sf::Vector2f);
        std::vector<sf::ConvexShape> m_light;
        std::vector<segment> m_lightSegmentList;
        sf::Color m_color;
        float m_radius;
        float m_angleStart; //m_angleStart < m_angleEnd in radian
        float m_angleEnd;   //for full circle m_angleStart=0, m_angleEnd=2*M_PI
        static const constexpr float RAY_STEP = Math::PI/24.f;
};
