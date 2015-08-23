//
//  monster.cpp
//  Monster
//
//  Created by Thibault Dardinier on 22/08/2015.
//  Copyright 2015 Thibault Dardinier. All rights reserved.
//

#include "monster.hpp"

void Monster::deplacer(sf::Vector2f movement)
{
    m_pos += movement;
};