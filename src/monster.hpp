//
//  monster.h
//  Monster
//
//  Created by Thibault Dardinier on 22/08/2015.
//  Copyright 2015 Thibault Dardinier. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Monster
{
public:
    sf::Vector2f m_pos;
    float m_jauge;
    float m_rayon;
    bool m_is_cache;
    void deplacer(sf::Vector2f movement);
};