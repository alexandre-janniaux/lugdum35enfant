//
//  IA_astar_reseau.cpp
//  Reseau
//
//  Created by Thibault Dardinier on 23/08/2015.
//  Copyright 2015 Thibault Dardinier. All rights reserved.
//

#include "IA_astar_reseau.hpp"

float distance_entre(sf::Vector2f point_a, sf::Vector2f point_b)
{
    sf::Vector2f diff = point_b - point_a;
    //return std::abs(diff.x) + std::abs(diff.y);
    //return sqrt(diff.x * diff.x + diff.y * diff.y);
    //return diff.x * diff.x + diff.y * diff.y;
    return std::max(std::abs(diff.x), std::abs(diff.y));
}

std::vector<int> getVoisins(int myNode, std::vector<Noeud> noeuds, std::vector<sf::FloatRect> obstacles)
{
    std::vector<int> voisins {};
    for (int k {0}; k < noeuds.size(); k++)
    {
        if (isVisible(noeuds[k].pos, noeuds[myNode].pos, obstacles) && k != myNode)
        {
            voisins.push_back(k);
        }
    }
    return voisins;
}

std::vector<int> AStar(int depart, int arrivee, std::vector<sf::Vector2f> points, std::vector<sf::FloatRect> obstacles)
{
    std::vector<int> closedList;
    std::list<int> openList;
    std::vector<Noeud> noeuds;
    for (sf::Vector2f point: points)
    {
        noeuds.push_back(Noeud (point, -1, std::numeric_limits<float>::infinity()));
    }
    noeuds[depart].distance = 0.;
    openList.push_back(depart);
    int id_min = -1;
    while (id_min != arrivee && !openList.empty())
    {
        // On chope le meilleur noeud
        id_min = openList.front();
        float distance_heuri_min = std::numeric_limits<float>::infinity();
        for (int i: openList)
        {
            float distance_heuri = noeuds[i].distance + distance_entre(noeuds[i].pos, noeuds[arrivee].pos);
            if (distance_heuri < distance_heuri_min)
            {
                distance_heuri_min = distance_heuri;
                id_min = i;
            }
        }
        
        // On l'enlève
        openList.remove(id_min);
        closedList.push_back(id_min);
        std::vector<int> voisins = getVoisins(id_min, noeuds, obstacles);
        for (int k: voisins)
        {
            if (!in(k, closedList))
            {
                // Deux cas : soit déjà vu, soit nouveau
                if (in(k, openList))
                {
                    // On actualise
                    float new_distance = noeuds[id_min].distance + distance_entre(noeuds[id_min].pos, noeuds[k].pos);
                    if (new_distance < noeuds[k].distance)
                    {
                        noeuds[k].distance = new_distance;
                        noeuds[k].parent = id_min;
                    }
                }
                else
                {
                    float new_distance = noeuds[id_min].distance + distance_entre(noeuds[id_min].pos, noeuds[k].pos);
                    noeuds[k].distance = new_distance;
                    noeuds[k].parent = id_min;
                    openList.push_back(k);
                }
            }
        }
    }
    if (id_min != arrivee)
    {
        return std::vector<int> {};
    }
    std::vector<int> chemin {arrivee};
    int actuel {arrivee};
    while (noeuds[actuel].parent != -1)
    {
        actuel = noeuds[actuel].parent;
        chemin.push_back(actuel);
    }
    std::vector<int> vrai_chemin (chemin.rbegin(), chemin.rend());
    return vrai_chemin;
}