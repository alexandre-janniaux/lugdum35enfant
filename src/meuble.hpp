//
//  meuble.hpp
//  Monster
//
//  Created by Thibault Dardinier on 22/08/2015.
//  Copyright 2015 Thibault Dardinier. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "monster.hpp"
#include "spritescenenode.hpp"

/* classe pour les lampes. */

class Lampe: public SpriteSceneNode
{
public:
    bool isLighting(sf::Vector2f point) const;
    void switcher();
private:
    sf::Vector2f m_origin;
    float m_rayon;
    bool m_isOn; 
};

/* classe virtuelle pure du meuble de base, avec lequel on intéragit,
 * et les classes héritées des meubles plus spécifiques.
 * Les fonctions "interact" sont spécifiques pour chaques meubles.
 */

enum Action {CACHER, ALLUMER, BRUITER, FINIR};

class Meuble: public SpriteSceneNode
{
public:
    virtual bool canInteract(sf::Vector2f point) const;
    virtual Action interact(Monster &me);
    virtual ~Meuble();
//private:
    sf::Sprite m_sprite;
    sf::FloatRect m_hitBox;
};

class Lit: public Meuble
{
public:
    virtual Action interact(Monster &me);
    virtual ~Lit();
};

class Cachette: public Meuble
{
public:
    virtual Action interact(Monster &me);
    virtual ~Cachette();
    bool m_used;
};

class Tapis: public Meuble
{
public:
    virtual bool canInteract(sf::Vector2f point) const;
    virtual Action interact(Monster &me);
    virtual ~Tapis();
//private:
    sf::FloatRect m_intHitBox;
    bool m_used;
};

class MeubleBruit: public Meuble
{
public:
    virtual Action interact(Monster &me);
    virtual ~MeubleBruit();
//private:
    sf::Time m_temps;
};

class Interrupteur: public Meuble
{
public:
    virtual Action interact(Monster &me);
    virtual ~Interrupteur();
//private:
    Lampe *m_light;
};
