#pragma once

//
//  IA_generate_ronde.h
//  Reseau
//
//  Created by Thibault Dardinier on 23/08/2015.
//  Copyright 2015 Thibault Dardinier. All rights reserved.
//

#include "IA_astar_grille.hpp"

std::vector<int> getOrdreCommerce(int depart, std::vector<sf::Vector2f> reseau, std::vector<sf::FloatRect> obstacles);

std::vector<sf::Vector2f> generateRonde(sf::FloatRect carte, std::vector<sf::FloatRect> obstacles, std::vector<sf::Vector2f> reseau, float pas);
