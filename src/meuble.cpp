//
//  meuble.cpp
//  Monster
//
//  Created by Thibault Dardinier on 22/08/2015.
//  Copyright 2015 Thibault Dardinier. All rights reserved.
//

#include "meuble.hpp"


/* Meuble */

bool Meuble::canInteract(sf::Vector2f point) const
{
    return m_hitBox.contains(point);
}

Action Meuble::interact(Monster &me)
{}

Meuble::~Meuble()
{}

bool Meuble::isObstacle()
{
    return true;
}

/* Lit */

Action Lit::interact(Monster &me)
{
    // TODO
    return FINIR;
}

Lit::~Lit()
{}


/* Cachette */

Action Cachette::interact(Monster &me)
{
    if (m_used)
    {
        m_used = false;
        me.m_is_cache = false;
    }
    else
    {
        m_used = true;
        me.m_is_cache = true;
    }
    return CACHER;
}

Cachette::~Cachette()
{}


/* Tapis */

bool Tapis::canInteract(sf::Vector2f point) const
{
    return Meuble::canInteract(point) && !m_hitBox.contains(point);
}

Action Tapis::interact(Monster &me)
{
    // TODO
    return CACHER;
}

Tapis::~Tapis()
{}

bool Tapis::isObstacle()
{
    return false;
}

/* MeubleBruit */

Action MeubleBruit::interact(Monster &me)
{
    // TODO
    return BRUITER;
}

MeubleBruit::~MeubleBruit()
{}


/* Interrupteur */

Action Interrupteur::interact(Monster &me)
{
    m_light->switcher();
}

Interrupteur::~Interrupteur()
{}



