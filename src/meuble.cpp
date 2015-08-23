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
{
    return BRUITER;// TODO À changer
}

Meuble::~Meuble()
{}


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
    // TODO
    return CACHER;
}

Cachette::~Cachette()
{}


/* Tapis */

bool Tapis::canInteract(sf::Vector2f point) const
{
    return Meuble::canInteract(point) && !m_intHitBox.contains(point);
}

Action Tapis::interact(Monster &me)
{
    // TODO
    return CACHER;
}

Tapis::~Tapis()
{}


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
    return BRUITER; // TODO À changer
}

Interrupteur::~Interrupteur()
{}



