//
//  IA_geometry.h
//  Reseau
//
//  Created by Thibault Dardinier on 23/08/2015.
//  Copyright 2015 Thibault Dardinier. All rights reserved.
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <list>
#include <cmath>
#include <ctime>

struct Segment {
    sf::Vector2f p1, p2;
    Segment() {};
    Segment(sf::Vector2f p1_, sf::Vector2f p2_)
    {
        p1 = p1_; p2 = p2_;
    };
    bool intersection(const Segment &other) const;
};

bool intersection(const Segment &other);

bool intersection(Segment mySegment, sf::FloatRect myRect);

bool contientPlus(sf::FloatRect rect, sf::Vector2f point);

bool isVisible(sf::Vector2f point_a, sf::Vector2f point_b, std::vector<sf::FloatRect> obstacles);

bool dansAucunObstacle(sf::Vector2f point, std::vector<sf::FloatRect> obstacles);