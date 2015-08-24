#pragma once

//
//  IA_astar_grille.h
//  Reseau
//
//  Created by Thibault Dardinier on 23/08/2015.
//  Copyright 2015 Thibault Dardinier. All rights reserved.
//

#include "IA_trouver_reseau.hpp"

int whereIsPointInNoeuds(sf::Vector2f point, std::vector<Noeud> table);

std::vector<sf::Vector2f> AStarGrille(sf::Vector2f depart, sf::Vector2f arrivee, std::vector<sf::FloatRect> obstacles, sf::Vector2f taille, float pas);
