//
//  meuble.cpp
//  Monster
//
//  Created by Thibault Dardinier on 22/08/2015.
//  Copyright 2015 Thibault Dardinier. All rights reserved.
//

#include "meuble.hpp"

/* Meuble */

bool Meuble::canInteract(sf::Vector2f point)
{
    return m_hitBox.contains(point);
}

void Meuble::interact(Monster &me)
{}

Meuble::~Meuble()
{}


/* Cachette */

void Cachette::interact(Monster &me)
{
    // TODO
}

Cachette::~Cachette()
{}


/* Tapis */

bool Tapis::canInteract(sf::Vector2f point)
{
    return Meuble::canInteract(point) && !m_intHitBox.contains(point);
}

void Tapis::interact(Monster &me)
{
    // TODO
}

Tapis::~Tapis()
{}


/* MeubleBruit */

void MeubleBruit::interact(Monster &me)
{
    // TODO
}

MeubleBruit::~MeubleBruit()
{}


/* Interrupteur */

void Interrupteur::interact(Monster &me)
{
    m_light->switcher();
}

Interrupteur::~Interrupteur()
{}


/* Lampe */

bool Lampe::isLighting(sf::Vector2f point)
{
    sf::Vector2f d = point - m_origin;
    return m_isOn && (d.x * d.x + d.y * d.y <= m_rayon * m_rayon);
}

void Lampe::switcher()
{
    m_isOn = !m_isOn;
}
