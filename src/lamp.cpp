#include "lamp.hpp"
#include "cpp_std_11.hpp"
#include <iostream>

Lamp::Lamp(sf::Color color,float radius, float angleStart,float angleEnd)
: m_color(color)
, m_radius(radius)
, m_angleStart(angleStart)
, m_angleEnd(angleEnd)
{
    setPosition(sf::Vector2f(0.f,0.f));
}

void Lamp::generateBaseRay()
{
    float _angle(m_angleStart);
    while (_angle+RAY_STEP<m_angleEnd)
    {
        Lamp::createRay(_angle,_angle+RAY_STEP);
        _angle+=RAY_STEP;
    }
    Lamp::createRay(_angle,m_angleEnd);
}

void Lamp::createRay(float angleStart, float angleEnd)
{
    sf::Vector2f _vec=getPosition();
    sf::Vector2f _pointA(cos(angleStart)*m_radius,sin(angleStart)*m_radius);
    sf::Vector2f _pointB(cos(angleEnd)*m_radius,sin(angleEnd)*m_radius);
    m_lightSegmentList.push_back(Segment(_pointA+_vec,_pointB+_vec));
}

std::vector<Segment> Lamp::rectangleToSegments(sf::Rect<float> const& rectangle)
{
    std::vector<Segment> result;
    result.clear();
    result.push_back(Segment(sf::Vector2f(rectangle.left,rectangle.top),
                             sf::Vector2f(rectangle.left,rectangle.top+rectangle.height)));
    result.push_back(Segment(sf::Vector2f(rectangle.left,rectangle.top+rectangle.height),
                             sf::Vector2f(rectangle.left+rectangle.width,rectangle.top+rectangle.height)));
    result.push_back(Segment(sf::Vector2f(rectangle.left+rectangle.width,rectangle.top),
                             sf::Vector2f(rectangle.left+rectangle.width,rectangle.top+rectangle.height)));
    result.push_back(Segment(sf::Vector2f(rectangle.left+rectangle.width,rectangle.top),
                             sf::Vector2f(rectangle.left,rectangle.top)));
    return result;
}

std::vector<Segment> Lamp::splitRay(Segment lightRay,Segment obstacle)
{
    std::vector<Segment> _newRays;
    _newRays.push_back(lightRay);
    return _newRays;
}

void Lamp::computeLight(std::vector<sf::Rect<float>> const& obstacles)
{
    m_lightSegmentList.clear();
    Lamp::generateBaseRay();
    std::vector<Segment> _newRays;
    std::vector<Segment> obstacleSegments;
    for (auto& obstacleRectangle : obstacles)
    {
        obstacleSegments = rectangleToSegments(obstacleRectangle);
        for (auto& obstacleSegment : obstacleSegments)
        {
            for (auto it=m_lightSegmentList.begin(); it!=m_lightSegmentList.end(); it++) {
                getPosition();
                obstacleSegment.intersection_triangle(getPosition(),*it,_newRays);
            }
            m_lightSegmentList.clear();
            for (auto it=_newRays.begin(); it!=_newRays.end(); it++) {
                m_lightSegmentList.push_back(*it);
            }
            _newRays.clear();
        }
    }
    m_lights.clear();
    m_children.clear();
    for (auto& it : m_lightSegmentList)
    {
        m_lights.push_back(make_unique<LightRay>(segmentToTriangle(it)));
        m_lights.back()->attachParent(this);
    }
}

sf::ConvexShape Lamp::segmentToTriangle(Segment segment)
{
    sf::ConvexShape triangle(3);
    triangle.setPoint(0,getPosition());
    triangle.setPoint(1,segment.p1);
    triangle.setPoint(2,segment.p2);
    triangle.setFillColor(m_color);
    return triangle;
}
