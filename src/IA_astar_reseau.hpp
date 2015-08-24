#pragma once

//
//  IA_astar_reseau.h
//  Reseau
//
//  Created by Thibault Dardinier on 23/08/2015.
//  Copyright 2015 Thibault Dardinier. All rights reserved.
//

#include "IA_geometry.hpp"

struct Noeud
{
    const sf::Vector2f pos;
    int parent;
    float distance;
    Noeud (sf::Vector2f p, int par, float d): pos(p), parent(par), distance(d){};
};

template <typename T>
bool in(T x, std::vector<T> v)
{
    return std::find(v.begin(), v.end(), x) != v.end();
}

template <typename T>
bool in(T x, std::list<T> v)
{
    return std::find(v.begin(), v.end(), x) != v.end();
}

float distance_entre(sf::Vector2f point_a, sf::Vector2f point_b);

std::vector<int> getVoisins(int myNode, std::vector<Noeud> noeuds, std::vector<sf::FloatRect> obstacles);

std::vector<int> AStar(int depart, int arrivee, std::vector<sf::Vector2f> points, std::vector<sf::FloatRect> obstacles);