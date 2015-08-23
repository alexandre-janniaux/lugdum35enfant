//
//  meuble.hpp
//  Monster
//
//  Created by Thibault Dardinier on 22/08/2015.
//  Copyright 2015 Thibault Dardinier. All rights reserved.
//
//TODO Utiliser SceneNode
//TODO Utiliser SceneNode
//TODO Utiliser SceneNode

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "lampes.hpp"

class Monster;

/* classe virtuelle pure du meuble de base, avec lequel on intéragit,
 * et les classes héritées des meubles plus spécifiques.
 * Les fonctions "interact" sont spécifiques pour chaques meubles.
 */

enum Action {CACHER, ALLUMER, BRUITER, FINIR};

class Meuble
{
public:
    inline Meuble(sf::Sprite const& sprite, sf::FloatRect const& hitbox) :
        m_sprite(sprite), m_hitBox(hitbox) {};
    virtual bool canInteract(sf::Vector2f point) const;
    virtual ~Meuble();
    virtual Action interact(Monster &me);
private:
    sf::Sprite m_sprite;
    sf::FloatRect const m_hitBox;
};

class Lit: public Meuble
{
public:
    inline Lit(sf::Sprite const& sprite, sf::FloatRect const& hitbox) :
        Meuble(sprite, hitbox), m_used(false) {};
    virtual ~Lit();
    virtual Action interact(Monster &me);
    bool m_used;
};

class Cachette: public Meuble
{
public:
    inline Cachette(sf::Sprite const& sprite, sf::FloatRect const& hitbox) :
        Meuble(sprite, hitbox), m_used(false) {};
    virtual ~Cachette();
    virtual Action interact(Monster &me);
    bool m_used;
};

class Tapis: public Meuble
{
public:
    inline Tapis(sf::Sprite const& sprite, sf::FloatRect const hitbox,
            sf::FloatRect const inhitbox) :
        Meuble(sprite, hitbox), m_inHitBox(inhitbox), m_used(false) {};
    virtual bool canInteract(sf::Vector2f point) const;
    virtual ~Tapis();
    virtual Action interact(Monster &me);
private:
    sf::FloatRect const m_inHitBox;
    bool m_used;
};

class MeubleBruit: public Meuble
{
public:
    inline MeubleBruit(sf::Sprite const& sprite, sf::FloatRect const hitbox, sf::Time time) :
        Meuble(sprite, hitbox), m_temps(time) {};
    virtual ~MeubleBruit();
    virtual Action interact(Monster &me);
private:
    sf::Time m_temps;
};

class Interrupteur: public Meuble
{
public:
    inline Interrupteur(sf::Sprite const& sprite, sf::FloatRect const& hitbox, int id_light) :
        Meuble(sprite, hitbox), m_id_light(id_light) {};
    virtual ~Interrupteur();
    virtual Action interact(Monster &me);
private:
    int m_id_light;
};
