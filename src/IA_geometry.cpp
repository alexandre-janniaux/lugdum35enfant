//
//  IA_geometry.cpp
//  Reseau
//
//  Created by Thibault Dardinier on 23/08/2015.
//  Copyright 2015 Thibault Dardinier. All rights reserved.
//

#include "IA_geometry.hpp"

const float epsilon = 1e-3f;

bool Segment::intersection(const Segment &other) const {
        
    sf::Vector2f dir1 = p2 - p1;
    sf::Vector2f dir2 = other.p2 - other.p1;
    /*
    Now we try to solve p1 + t1 * dir1 = other.p1 + t2 * dir2
    This is a system of two linear equations
    */
    float a = dir1.x;
    float b = -dir2.x;
    float c = dir1.y;
    float d = -dir2.y;
    float det = (a * d - b * c);
    if (-epsilon <= det && det <= epsilon) {
        return false;
    }
    float e = other.p1.x - p1.x;
    float f = other.p1.y - p1.y;
    float t1 = (d * e - b * f) / det;
    float t2 = (-c * e + a * f) / det;
    if (-epsilon <= t1 && t1 <= 1 + epsilon && -epsilon <= t2 && t2 <= 1 + epsilon)
    {
        return true;
    }
    return false;
};

bool intersection(Segment mySegment, sf::FloatRect myRect)
{
    Segment s1, s2, s3, s4;
    s1.p1 = sf::Vector2f (myRect.left, myRect.top);
    s1.p2 = sf::Vector2f (myRect.left, myRect.top + myRect.height);
    
    s2.p1 = sf::Vector2f (myRect.left + myRect.width, myRect.top);
    s2.p2 = sf::Vector2f (myRect.left + myRect.width, myRect.top + myRect.height);
    
    s3.p1 = sf::Vector2f (myRect.left, myRect.top + myRect.height);
    s3.p2 = sf::Vector2f (myRect.left + myRect.width, myRect.top + myRect.height);
    
    s4.p1 = sf::Vector2f (myRect.left, myRect.top);
    s4.p2 = sf::Vector2f (myRect.left + myRect.width, myRect.top);
    
    return mySegment.intersection(s1) || mySegment.intersection(s2) || mySegment.intersection(s3) || mySegment.intersection(s4);
}

bool contientPlus(sf::FloatRect rect, sf::Vector2f point)
{
    sf::FloatRect rect2 (rect.left - epsilon, rect.top - epsilon, rect.width + 2 * epsilon, rect.height + 2 * epsilon);
    return rect2.contains(point);
}

bool isVisible(sf::Vector2f point_a, sf::Vector2f point_b, std::vector<sf::FloatRect> obstacles)
{
    bool visible {true};
    for (auto rect: obstacles)
    {
        Segment mySegment (point_a, point_b);
        visible = visible && !(intersection(mySegment, rect));
    }
    return visible;
}

bool dansAucunObstacle(sf::Vector2f point, std::vector<sf::FloatRect> obstacles)
{
    bool b {true};
    for (sf::FloatRect rect: obstacles)
    {
        b = b && !(contientPlus(rect, point));
    }
    return b;
}