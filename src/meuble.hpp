//
//  meuble.hpp
//  Monster
//
//  Created by Thibault Dardinier on 22/08/2015.
//  Copyright 2015 Thibault Dardinier. All rights reserved.
//
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "monster.hpp"
#include "lampes.hpp"
#include "spritescenenode.hpp"
#include "entitypool.hpp"

/* classe virtuelle pure du meuble de base, avec lequel on intéragit,
 * et les classes héritées des meubles plus spécifiques.
 * Les fonctions "interact" sont spécifiques pour chaques meubles.
 */

enum Action {CACHER, ALLUMER, BRUITER, FINIR};

class GameContext;

class Meuble
{
public:
    Meuble(sf::Sprite &sprite, sf::Vector2f pos, sf::FloatRect hitBox, sf::FloatRect interactBox, GameContext& context);
    virtual bool canInteract(sf::Vector2f point) const;
    virtual Action interact(Monster &me);
    virtual ~Meuble();
    virtual bool isObstacle();
//private:
	Entity m_entity;
    SpriteSceneNode m_sn;
    sf::FloatRect m_hitBox;
    sf::FloatRect m_interactBox;
};

class Lit: public Meuble
{
public:
    inline Lit(sf::Sprite &sprite, sf::Vector2f pos, sf::FloatRect hitBox, sf::FloatRect interactBox, GameContext& context) : Meuble(sprite, pos, hitBox, interactBox, context) {};
        
    virtual Action interact(Monster &me);
    virtual ~Lit();
};

class Cachette: public Meuble
{
public:
    inline Cachette(sf::Sprite &sprite, sf::Vector2f pos, sf::FloatRect hitBox, sf::FloatRect interactBox, GameContext& context) : Meuble(sprite, pos, hitBox, interactBox, context), m_used(false) {};

    virtual Action interact(Monster &me);
    virtual ~Cachette();
private:
    bool m_used;
};

class Tapis: public Meuble
{
public:
    inline Tapis(sf::Sprite &sprite, sf::Vector2f pos, sf::FloatRect hitBox, sf::FloatRect interactBox, GameContext& context) : Meuble(sprite, pos, hitBox, interactBox, context), m_used(false) {};

    virtual bool canInteract(sf::Vector2f point) const;
    virtual Action interact(Monster &me);
    virtual ~Tapis();
    virtual bool isObstacle();
private:
    bool m_used;
};

class MeubleBruit: public Meuble
{
public:
    inline MeubleBruit(sf::Sprite &sprite, sf::Vector2f pos, sf::FloatRect hitBox, sf::FloatRect interactBox, sf::Time time, GameContext& context) : Meuble(sprite, pos, hitBox, interactBox, context), m_temps(time) {};

    virtual Action interact(Monster &me);
    virtual ~MeubleBruit();
private:
    sf::Time m_temps;
};

class Interrupteur: public Meuble
{
public:
    inline Interrupteur(sf::Sprite &sprite, sf::Vector2f pos, sf::FloatRect hitBox, sf::FloatRect interactBox, Lampe &light, GameContext& context) : Meuble(sprite, pos, hitBox, interactBox, context), m_light(&light) {};

    virtual Action interact(Monster &me);
    virtual ~Interrupteur();
private:
    Lampe *m_light;
};
