//
//  meuble.hpp
//  Monster
//
//  Created by Thibault Dardinier on 22/08/2015.
//  Copyright 2015 Thibault Dardinier. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Monster;

/* classe pour les lampes. */

class Lampe
{
public:
    bool isLighting(sf::Vector2f point);
    bool switcher();
private:
    sf::Vector2f m_origin;
    float m_rayon;
    bool m_isOn;
};


/* classe virtuelle pure du meuble de base, avec lequel on intéragit,
 * et les classes héritées des meubles plus spécifiques.
 * Les fonctions "interact" sont spécifiques pour chaques meubles.
 */

class Meuble
{
public:
    virtual bool canInteract(sf::Vector2f point);
    virtual void interact(Monster &me);
    virtual ~Meuble();
private:
    sf::Sprite const m_sprite;
    sf::FloatRect const m_hitBox;
};

class Cachette: public Meuble
{
public:
    virtual void interact(Monster &me);
    virtual ~Cachette();
private:
    bool m_used;
};

class Tapis: public Meuble
{
public:
    virtual bool canInteract(sf::Vector2f point);
    virtual void interact(Monster &me);
    virtual ~Tapis();
private:
    sf::FloatRect const m_intHitBox;
    bool m_used;
};

class MeubleBruit: public Meuble
{
public:
    virtual void interact(Monster &me);
    virtual ~MeubleBruit();
private:
    sf::Time m_temps;
};

class Interrupteur: public Meuble
{
public:
    virtual void interact(Monster &me);
    virtual ~Interrupteur();
private:
    Lampe *m_light;
};


