#include "lamp.hpp"

/*
void Lamp::distance(sf::Vector2f point)
{
    return sqrt(point.x*point.x+point.y*point.y);
}
*/

void Lamp::addRay(sf::Vector2f pointA,sf::Vector2f pointB)
{
    /*
    sf::ConvexShape _triangle(3);
    _triangle.setPoint(0,sf::Vector2f(0.f,0.f));
    _triangle.setPoint(1,pointA);
    _triangle.setPoint(2,pointB);
    _triangle.setFillColor(m_color);
    m_light.push_back(_triangle);
    */
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
    sf::Vector2f _pointA(cos(angleStart)*m_radius,sin(angleStart)*m_radius);
    sf::Vector2f _pointB(cos(angleEnd)*m_radius,sin(angleEnd)*m_radius);
    m_lightSegmentList.push_back(Segment(_pointA,_pointB));
}

std::vector<Segment> Lamp::rectangleToSegments(sf::Rect<float> const& rectangle)
{
    std::vector<Segment> result;
    result.push_back(Segment(sf::Vector2f(rectangle.left,rectangle.top),sf::Vector2f(rectangle.left,rectangle.top+rectangle.height)));
    result.push_back(Segment(sf::Vector2f(rectangle.left,rectangle.top+rectangle.height),sf::Vector2f(rectangle.left+rectangle.width,rectangle.top+rectangle.height)));
    result.push_back(Segment(sf::Vector2f(rectangle.left+rectangle.width,rectangle.top+rectangle.height),sf::Vector2f(rectangle.left+rectangle.width,rectangle.top+rectangle.height)));
    result.push_back(Segment(sf::Vector2f(rectangle.left+rectangle.width,rectangle.top),sf::Vector2f(rectangle.left,rectangle.top)));
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
            auto it=m_lightSegmentList.begin();
            while (it!=m_lightSegmentList.end())
            {
                _newRays=Lamp::splitRay(*it,obstacleSegment);
                *it=_newRays.back();
                _newRays.pop_back();
                while (!_newRays.empty())
                {
                    m_lightSegmentList.push_back(_newRays.back());
                    _newRays.pop_back();
                }
                it++;
            }
        }
    }
}
