#pragma once
#include <SFML/Graphics.hpp>
#include "scenenode.hpp"
#include "geometry.hpp"
#include "lightray.hpp"
#include <cmath>
#include <memory>


namespace Math
{
	constexpr const float PI=3.14159265358979f;
}

class Lamp : public SceneNode
{
    public:
        Lamp(sf::Color,float,float,float);
        void computeLight(std::vector<sf::Rect<float>> const&);
        void addRay(sf::Vector2f, sf::Vector2f);

    private:
        void generateBaseRay();
        void createRay(float, float);
        std::vector<Segment> splitRay(Segment,Segment);
        std::vector<Segment> rectangleToSegments(sf::Rect<float> const&);
        void buildRays();
        sf::ConvexShape segmentToTriangle(Segment);

    private:
        bool m_computedLight;
        //static float distance(sf::Vector2f);
        std::vector<std::unique_ptr<LightRay>> m_lights;
        std::vector<Segment> m_lightSegmentList;
        sf::Color m_color;
        float m_radius;
        float m_angleStart; //m_angleStart < m_angleEnd in radian
        float m_angleEnd;   //for full circle m_angleStart=0, m_angleEnd=2*M_PI
        static const constexpr float RAY_STEP = Math::PI/12.f;
};
