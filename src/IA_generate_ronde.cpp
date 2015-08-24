//
//  IA_generate_ronde.cpp
//  Reseau
//
//  Created by Thibault Dardinier on 23/08/2015.
//  Copyright 2015 Thibault Dardinier. All rights reserved.
//

#include "IA_generate_ronde.hpp"

std::vector<int> getOrdreCommerce(int depart, std::vector<sf::Vector2f> reseau, std::vector<sf::FloatRect> obstacles)
{
    std::list<int> restant {};
    std::vector<int> chemin {depart};
    int actuel = depart;
    for (int k {0}; k < reseau.size(); k++)
    {
        if (k != depart)
        {
            restant.push_back(k);
        }
    }
    
    while (!restant.empty())
    {
        // On prend le meilleur noeud a priori
        float distance_noeuds_mini = std::numeric_limits<float>::infinity();
        int id_min = restant.front();
        float distance_oiseau_mini = std::numeric_limits<float>::infinity();
        for (int id: restant)
        {
            std::cout << "B";
            auto chemin = AStar(actuel, id, reseau, obstacles);
            float distance_noeuds = chemin.size();
            if (distance_noeuds == 0)
            {
                distance_noeuds = std::numeric_limits<float>::infinity();
            }
            std::cout << "A";
            float distance_oiseau = distance_entre(reseau[actuel], reseau[id]);
            if (distance_noeuds < distance_noeuds_mini || (distance_noeuds == distance_noeuds_mini && distance_oiseau < distance_oiseau_mini))
            {
                id_min = id;
                distance_oiseau_mini = distance_oiseau;
                distance_noeuds_mini = distance_noeuds;
            }
        }
        
        // id_min est le bon
        restant.remove(id_min);
        actuel = id_min;
        chemin.push_back(id_min);
    }
    printer(chemin);
    return chemin;
}

std::vector<sf::Vector2f> generateRonde(sf::FloatRect carte, std::vector<sf::FloatRect> obstacles, std::vector<sf::Vector2f> reseau, float pas)
{
    // On part du dernier
    int depart = reseau.size() - 1;
    std::vector<int> chemin_commerce = getOrdreCommerce(depart, reseau, obstacles);
    std::vector<sf::Vector2f> chemin_global {reseau[depart]};
    for (int k {0}; k + 1 < chemin_commerce.size(); k++)
    {
        std::cout << std::endl << "En cours de calcul... " << k << std::endl;
        std::vector<sf::Vector2f> chemin_partiel = AStarGrille(reseau[chemin_commerce[k]], reseau[chemin_commerce[k + 1]], obstacles, sf::Vector2f (carte.width, carte.height), pas);
        for (int i {1}; i < chemin_partiel.size(); i++)
        {
            chemin_global.push_back(chemin_partiel[i]);
        }
    }
    int k = chemin_commerce.size() - 1;
    std::vector<sf::Vector2f> chemin_partiel = AStarGrille(reseau[chemin_commerce[k]], reseau[chemin_commerce[0]], obstacles, sf::Vector2f (carte.width, carte.height), pas);
    for (int i {1}; i < chemin_partiel.size(); i++)
    {
        chemin_global.push_back(chemin_partiel[i]);
    }
    return chemin_global;
}